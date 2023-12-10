FROM rust:slim-bookworm

RUN apt-get update && apt-get install -y pkg-config make clang libusb-1.0-0 libusb-1.0-0-dev
RUN rustup component add rustfmt clippy
RUN cargo install cargo-deb cargo-sort
WORKDIR /workdir
