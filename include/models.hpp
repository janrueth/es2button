#include <unistd.h>
#include <map>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

#include <config.h>

class ESModelInfos {
    private:
        std::unordered_map<int,std::string> pid_to_model;

    public:
        ESModelInfos() {  // Constructor
            // walk the model_path and look for model files and
            // get the .HardwareInfo[0].ESModelID.string
            // get .HardwareInfo[0].ESProductID.string -> hex to int
            // add to pid_to_model
            for (const auto& dirEntry : recursive_directory_iterator(EPSONSCAN2_LIB_PATH "Resources/Models/")) {
                if (!dirEntry.is_regular_file() || 
                    dirEntry.path().filename() == "ConvertTable.json" || 
                    dirEntry.path().extension() != ".json" ||
                    dirEntry.path().string().rfind(EPSONSCAN2_LIB_PATH "Resources/Models/ES", 0) != 0) {
                    continue;
                }
                
                std::ifstream ifs(dirEntry.path().string().c_str(), std::ifstream::in);

                auto esmodel = json::parse(ifs);
                std::string pid = esmodel.value(json::json_pointer("/HardwareInfo/0/ESProductID/string"), "");
                std::string modelID = esmodel.value(json::json_pointer("/HardwareInfo/0/ESModelID/string"), "");
                
                if (pid.empty() || modelID.empty()) {
                    continue;
                }
                // pid is hex but we need decimal
                int pid_int = std::stoul(pid, nullptr, 16);
                pid_to_model[pid_int] = modelID;
            }
        }

        char const* model_name_for_pid(int pid) {
            if (auto search = pid_to_model.find(pid); search != pid_to_model.end()) {
                return search->second.c_str();
            }

            return "";
        }
};