
all: build deb

.PHONY: fmt
fmt:
	cargo fmt --all
	cargo sort

.PHONY: lint
lint:
	cargo fmt --all --check
	cargo clippy --workspace --all-targets
	cargo sort -c

.PHONY: test
test:
	cargo test --all-targets

build:
	cargo build --release -p es2button

deb:
ifeq ($(TARGET),) 
	cargo deb -p es2button --no-build -o target/debian/
else
	cargo deb -p es2button --no-build --target $(TARGET) -o target/debian/
endif

build-cross:
	cross build -p es2button --target $(TARGET) --release

.PHONY: enter-docker
enter-docker:
	docker build -t es2button-builder . && docker run -it -v $(shell pwd):/workdir -t es2button-builder /bin/bash
