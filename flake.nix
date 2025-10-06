{
  description = "A Nix-flake-based development environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-25.05";
  };

  outputs = { self , nixpkgs ,... }: let
    # system should match the system you are running on
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {
        inherit system;
      };
    in pkgs.mkShell {
      packages = with pkgs; [

      ];

      buildInputs = with pkgs; [
        meson
        pkg-config
        gcc
        cmake
        ninja
        python3
        yaml-cpp
        notcurses
      ];

      shellHook = ''
        export PKG_CONFIG_PATH=${pkgs.notcurses}/lib/pkgconfig:$PKG_CONFIG_PATH
        echo "Entered dev env"
      '';
    };
  };
}