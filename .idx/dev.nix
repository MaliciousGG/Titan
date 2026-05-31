# To learn more about how to use Nix to configure your environment
# see: https://developers.google.com/idx/guides/customize-idx-env
{ pkgs, ... }: {
  channel = "stable-24.05";

  packages = [
    pkgs.gcc
    pkgs.clang
    pkgs.clang-tools
    pkgs.libcxx
    pkgs.cmake
    pkgs.ninja
    pkgs.gdb
    pkgs.pkg-config

    pkgs.docker
    pkgs.docker-compose
  ];

  services.docker = {
    enable = true;
  };

  env = {};

  idx = {
    extensions = [
      "llvm-vs-code-extensions.vscode-clangd"
      "vadimcn.vscode-lldb"
      "google.gemini-cli-vscode-ide-companion"
    ];
  };
}