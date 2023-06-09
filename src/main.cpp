
#include <libusb-1.0/libusb.h>
#include <signal.h>
#include <unistd.h>

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// these are from the epsonscan2 src
#include <Include/Controller/EpsonScan2.h>
#include <Include/ES2Command/ES2CommandAPI.h>

// this is generated by cmake
#include <config.h>

void print_usage(char* argv[]) {
  printf("Usage: %s [-l] [-d DEVNAME] PROGRAM\n", argv[0]);
  printf("\n");
  printf(" -l\t\tList devices\n");
  printf(" -d DEVNAME\tUse device, e.g., ES-310:006:001\n");
}

static const uint32_t kEpsonUSBVID = 0x04b8;

typedef struct {
  unsigned char name[255];
  int vid;
  int pid;
  int bus;
  int dev;
} USBDevice;

class ESListener : public IESScannerDelegate {
 private:
  IESScanner* _scanner;
  const char* _prog;
  USBDevice _dev;
  PFN_CREATE_SCANNER _create_scanner_fn;

  ESErrorCode read_bool_value(const char* key, bool* b) {
    CESResultString res;
    ESErrorCode eErrorCode;
    eErrorCode = _scanner->GetValueForKey(key, &res);
    if (eErrorCode != kESErrorNoError) {
      return eErrorCode;
    }
    json resp = json::parse(res.Get());
    *b = resp[key]["boolean"];
    return kESErrorNoError;
  }

 public:
  ESListener() {  // Constructor
    void* handle = dlopen(EPSONSCAN2_LIB_PATH "libes2command.so", RTLD_LAZY);
    if (!handle) {
      perror(dlerror());
      exit(EXIT_FAILURE);
    }
    _create_scanner_fn = (PFN_CREATE_SCANNER)dlsym(handle, "ESCreateScanner");
    if (_create_scanner_fn == NULL) {
      printf("Could not find ESCreateScanner in libes2command.so");
      exit(EXIT_FAILURE);
    }
  }
  void showGetAllAvailableValues() {
    CESResultString res;
    ESErrorCode eErrorCode;
    eErrorCode = _scanner->GetAllAvailableValues(&res);
    if (eErrorCode != kESErrorNoError) {
      printf("failed GetAllAvailableValues: %d", eErrorCode);
      return;
    }
    printf("%s\n", res.Get());
  }

  void showGetAllValues() {
    CESResultString res;
    ESErrorCode eErrorCode;
    eErrorCode = _scanner->GetAllValues(&res);
    if (eErrorCode != kESErrorNoError) {
      printf("failed GetAllValues: %d", eErrorCode);
      return;
    }
    printf("%s\n", res.Get());
  }
  std::vector<USBDevice> getEpsonDevices() {
    std::vector<USBDevice> result;

    libusb_context* pContext;
    libusb_device** ppDeviceList;
    libusb_device_descriptor oDeviceDescriptor;
    libusb_device_handle* hHandle;

    int iReturnValue = libusb_init(&pContext);
    if (iReturnValue != LIBUSB_SUCCESS) {
      return result;
    }

    ssize_t nbUsbDevices = libusb_get_device_list(pContext, &ppDeviceList);

    for (ssize_t i = 0; i < nbUsbDevices; ++i) {
      libusb_device* pDevice = ppDeviceList[i];
      iReturnValue = libusb_get_device_descriptor(pDevice, &oDeviceDescriptor);
      if (iReturnValue != LIBUSB_SUCCESS) {
        continue;
      }
      if (oDeviceDescriptor.idVendor != kEpsonUSBVID) {
        continue;
      }
      iReturnValue = libusb_open(pDevice, &hHandle);
      if (iReturnValue != LIBUSB_SUCCESS) {
        printf("failed opening usb device\n");
        continue;
      }
      iReturnValue = libusb_reset_device(hHandle);
      if (iReturnValue != LIBUSB_SUCCESS) {
        printf("failed resetting usb device\n");
        libusb_close(hHandle);
        continue;
      }

      USBDevice dev;

      int iProductNameSize = libusb_get_string_descriptor_ascii(
          hHandle, oDeviceDescriptor.iProduct, dev.name, sizeof(dev.name));
      if (iProductNameSize <= 0) {
        printf("LIBUSB ERR: %d", iProductNameSize);
        memcpy(dev.name, "Failed getting name", 20);
      }

      dev.bus = libusb_get_bus_number(pDevice);
      dev.dev = libusb_get_device_address(pDevice);
      dev.vid = oDeviceDescriptor.idVendor;
      dev.pid = oDeviceDescriptor.idProduct;

      result.push_back(dev);

      libusb_close(hHandle);
    }

    libusb_free_device_list(ppDeviceList, 1);
    libusb_exit(pContext);

    return result;
  }
  ESErrorCode init(USBDevice* dev, const char* prog) {
    _dev = *dev;
    ESErrorCode eErrorCode = _create_scanner_fn(kESCommandTypeESCI2, &_scanner);

    if (eErrorCode != kESErrorNoError) {
      perror("failed aquiring scanner engine");
      return eErrorCode;
    }

    // todo discover usb devices with VID=0x04b8

    json esDeviceDict = {
        {ES_CNCT_KEY_ROOT,
         {{{ES_CNCT_KEY_TYPE, {{"int", kESConnectionLocal}}},
           {ES_CNCT_KEY_VID, {{"int", _dev.vid}}},
           {ES_CNCT_KEY_PID, {{"int", _dev.pid}}},
           {ES_CNCT_KEY_BUS_NUMBER, {{"int", _dev.bus}}},
           {ES_CNCT_KEY_DEVICE_NUMBER, {{"int", _dev.dev}}}}}}};

    std::string serialized_string = esDeviceDict.dump(1);

    _scanner->SetConnection(serialized_string.c_str());

    _scanner->SetDelegate(this);

    _prog = prog;

    eErrorCode = _scanner->Open();
    if (eErrorCode != kESErrorNoError) {
      perror("failed aquiring scanner engine");
      return eErrorCode;
    }
    return kESErrorNoError;
  }

  void listen() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);

    int sig;
    sigwait(&set, &sig);
    switch (sig) {
      case SIGINT:
        printf("Terminating\n");
        break;
      case SIGPIPE:
        printf("Stopping scanner is gone\n");
        break;
    }

    _scanner->Close();
    _scanner->DestroyInstance();
  }

  bool IsDocumentLoaded() {
    bool res;
    if (read_bool_value(kESDocumentLoaded, &res) != kESErrorNoError) {
      printf("Failed checking document status\n");
      return false;
    }
    return res;
  }

  bool IsCardScanning() {
    bool res;
    if (read_bool_value(kESCardScanning, &res) != kESErrorNoError) {
      printf("Failed checking card scanning status\n");
      return false;
    }
    return res;
  }

  // Delegate methods below

  void ScannerDidEncounterDeviceCommunicationError(IESScanner* pScanner,
                                                   ESErrorCode err) {
    printf("Communication Error: %d\n", __PRETTY_FUNCTION__, err);
    //  wakeup listener
    kill(getpid(), SIGPIPE);
  };

  void ScannerDidPressButton(UInt8 un8ButtonNumber) {
    // printf("%s: %d was pressed\n", __PRETTY_FUNCTION__, un8ButtonNumber);

    ESErrorCode eErrorCode;
    auto docLoaded = this->IsDocumentLoaded();
    auto cardScanning = this->IsCardScanning();

    _scanner->Close();

    char buttonNumEnvStr[4];

    sprintf(buttonNumEnvStr, "%d", un8ButtonNumber);
    setenv("ES2_BUTTON_NUM", buttonNumEnvStr, 1);  // Overwrite it
    setenv("ES2_DOC_PRESENT", docLoaded ? "Yes" : "No",
           1);  // Overwrite it
    setenv("ES2_CARD_SCANNING", cardScanning ? "Yes" : "No",
           1);  // Overwrite it

    char device[sizeof(_dev.name) + 1 + 3 + 1 + 3 + 1];  // dev:000:000\0
    char vid[5];
    char pid[5];

    sprintf(device, "%s:%03d:%03d", _dev.name, _dev.bus, _dev.dev);
    sprintf(vid, "%04X", _dev.vid);
    sprintf(pid, "%04X", _dev.pid);

    setenv("ES2_DEV", device, 1);   // Overwrite it
    setenv("ES2_DEV_VID", vid, 1);  // Overwrite it
    setenv("ES2_DEV_PID", pid, 1);  // Overwrite it
    printf("Calling script: %s\n", _prog);

    system(_prog);

    printf("Resuming from script\n");
    _scanner->Open();
  };

  void ScannerWillBeginContinuousScanning(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidEndContinuousScanning(IESScanner* pScanenr) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerWillScanToScannedImage(IESScanner* pScanner,
                                     IESScannedImage* pESImage) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidScanToScannedImage(IESScanner* pScanner,
                                    IESScannedImage* pESImage) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerWillCancelScanning(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidCancelScanning(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidCompleteScanningWithError(IESScanner* pScanner,
                                           ESErrorCode err) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidInterruptScanningWithError(IESScanner* pcScanner,
                                            ESErrorCode err) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerWillWarmUp(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidWarmUp(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void NetworkScannerDidRequestStartScanning(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void NetworkScannerDidRequestStopScanning(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidDisconnect(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void NetworkScannerDidReceiveServerError(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  BOOL NetworkScannerShouldPreventTimeout(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
  };

  void NetworkScannerDidTimeout(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerIsReservedByHost(IESScanner* pScanner,
                               const ES_CHAR* pszAddress) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidRequestStop(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };

  void ScannerDidRequestPushScanConnection(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };
  void ScannerDidNotifyStatusChange(IESScanner* pScanner) {
    printf("%s\n", __PRETTY_FUNCTION__);
  };
};

int main(int argc, char* argv[]) {
  ESListener listener;
  ESErrorCode err;

  auto devices = listener.getEpsonDevices();
  USBDevice dev;
  memset(&dev, 0, sizeof(dev));
  for (;;) {
    switch (
        getopt(argc, argv, "ld:h"))  // note the colon (:) to indicate that 'b'
                                     // has a parameter and is not a switch
    {
      case 'l': {
        for (auto d : devices) {
          printf("%s:%03d:%03d\n", d.name, d.bus, d.dev);
        }
        return 0;
      }

      case 'd': {
        char* dev_name = strtok(optarg, ":");
        char* dev_bus = strtok(NULL, ":");
        char* dev_dev = strtok(NULL, ":");

        printf("%s %d %d", dev_name, atoi(dev_bus), atoi(dev_dev));
        if (devices.empty()) {
          printf("No devices found\n");
          return 0;
        }

        for (auto d : devices) {
          if (dev_name != NULL && strcmp((const char*)d.name, dev_name) != 0) {
            continue;
          }
          if (dev_bus != NULL && atoi(dev_bus) != d.bus) {
            continue;
          }
          if (dev_dev != NULL && atoi(dev_dev) != d.dev) {
            continue;
          }
          dev = d;

          break;
        }
        if (dev.vid == 0) {
          printf("Device not found\n");
          return 1;
        }
        continue;
      }

      case '?':
      case 'h': {
        print_usage(argv);
        return 0;
      }

      case -1: {
        if (dev.vid == 0) {  // no device set yet
          if (devices.empty()) {
            printf("No devices found\n");
            return 0;
          }
          dev = devices.at(0);
        }
        break;
      }
    }
    break;
  }

  char* prog = (char*)ES2CONF_DIR "/entrypoint";
  if (optind >= argc) {
    printf("No program specified, falling back to default\n\n");
  }else {
    prog = argv[optind];
  }

  printf("Using \"%s\" as program to call\n", prog);

  printf("Initializing %s, vid=%04X, pid=%04X, bus=%03d, dev=%03d\n", dev.name,
         dev.vid, dev.pid, dev.bus, dev.dev);

  err = listener.init(&dev, prog);
  if (err != kESErrorNoError) {
    return err;
  }

  // listener.showGetAllAvailableValues();

  // listener.showGetAllValues();

  listener.listen();
}
