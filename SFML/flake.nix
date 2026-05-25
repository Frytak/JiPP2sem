{
    description = "";

    inputs = {
        nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.11";
        flake-parts.url = "github:hercules-ci/flake-parts";
    };

    outputs =
        inputs@{ self, flake-parts, ... }:
        flake-parts.lib.mkFlake { inherit inputs; } {
            systems = [
                "x86_64-linux"
                "aarch64-linux"
                "aarch64-darwin"
                "x86_64-darwin"
            ];

            imports = [ ];

            perSystem =
                {
                    pkgs,
                    ...
                }:
                let
                    # SheenBidi — new dep introduced in SFML 3.1.0
                    # Check the exact GIT_TAG used in:
                    # https://github.com/SFML/SFML/blob/3.1.0/src/SFML/Graphics/CMakeLists.txt
                    sheenbidi = pkgs.stdenv.mkDerivation {
                        pname = "sheenbidi";
                        version = "2.7";  # verify against SFML's CMakeLists.txt

                        src = pkgs.fetchFromGitHub {
                            owner = "Tehreer";
                            repo = "SheenBidi";
                            rev = "v3.0.0";  # verify this tag
                            hash = "sha256-e/24MlRX+93b34qD2V1+2XVhMh4WEy2qvt9Rgvybwxs="; # replace
                        };

                        nativeBuildInputs = [ pkgs.cmake ];

                        # SheenBidi's CMake installs a proper find_package config
                        cmakeFlags = [
                            "-DCMAKE_BUILD_TYPE=Release"
                            "-DCMAKE_INSTALL_INCLUDEDIR=include"
                            "-DCMAKE_INSTALL_LIBDIR=lib"
                        ];
                    };

                    # cpp-unicodelib — header-only, also new in SFML 3.1.0
                    # Check the GIT_TAG in SFML's CMakeLists.txt for the right commit/tag
                    cpp-unicodelib = pkgs.stdenv.mkDerivation {
                        pname = "cpp-unicodelib";
                        version = "unstable-2024";

                        src = pkgs.fetchFromGitHub {
                            owner = "yhirose";
                            repo = "cpp-unicodelib";
                            rev = "master"; # replace with the exact commit SFML pins
                            hash = "sha256-ioh2w5sIjgj1hplw+e4msBvbW3YkssZWrJO9tJDD4CE="; # replace
                        };

                        # Header-only: just copy the header into $out/include
                        installPhase = ''
                            mkdir -p $out/include
                            cp -r * $out/include/
                        '';

                        dontBuild = true;
                    };

                    sheenbidi-src = pkgs.fetchFromGitHub {
                        owner = "Tehreer";
                        repo = "SheenBidi";
                        rev = "v3.0.0";  # verify this tag
                        hash = "sha256-e/24MlRX+93b34qD2V1+2XVhMh4WEy2qvt9Rgvybwxs="; # replace
                    };

                    cpp-unicodelib-src = pkgs.fetchFromGitHub {
                        owner = "yhirose";
                        repo = "cpp-unicodelib";
                        rev = "master"; # replace with the exact commit SFML pins
                        hash = "sha256-ioh2w5sIjgj1hplw+e4msBvbW3YkssZWrJO9tJDD4CE="; # replace
                    };

                    sfml_3_1_0 = pkgs.sfml.overrideAttrs (oldAttrs: {
                        version = "3.1.0";

                        src = pkgs.fetchFromGitHub {
                            owner = "SFML";
                            repo = "SFML";
                            rev = "3.1.0";
                            hash = "sha256-DNtOFeabU3yY1AoNS2kKZZAKdYNgPNkqG32PhY6YBDY=";
                        };

                        patches = [ ];

                        buildInputs = oldAttrs.buildInputs ++ [
                            pkgs.harfbuzz
                            pkgs.mbedtls
                            pkgs.libssh2
                            pkgs.glib
                            pkgs.libsysprof-capture
                            pkgs.pcre2
                        ];

                        cmakeFlags = (oldAttrs.cmakeFlags or [ ]) ++ [
                            "-DSFML_USE_SYSTEM_DEPS=ON"

                            # Point FetchContent at the pre-fetched sources.
                            # The variable name is FETCHCONTENT_SOURCE_DIR_<UPPERCASE_NAME>
                            # where the name matches FetchContent_Declare(...) in SFML's CMakeLists.
                            # Verify the exact names used by SFML in:
                            # src/SFML/Graphics/CMakeLists.txt
                            "-DFETCHCONTENT_SOURCE_DIR_SHEENBIDI=${sheenbidi-src}"
                            "-DFETCHCONTENT_SOURCE_DIR_CPP-UNICODELIB=${cpp-unicodelib-src}"

                            # UPDATES_DISCONNECTED skips the git update/clone step
                            # but STILL runs add_subdirectory (unlike FULLY_DISCONNECTED
                            # which skips add_subdirectory and breaks target creation).
                            "-DFETCHCONTENT_UPDATES_DISCONNECTED=ON"
                        ];

                        postInstall = (oldAttrs.postInstall or "") + ''
                            rm -f $out/lib/pkgconfig/sheenbidi.pc
                        '';
                    });
                in
                {
                    devShells.default = pkgs.mkShell {
                        name = "SFML";

                        packages = with pkgs; [
                            gcc
                            pkg-config
                            cmake
                            sfml_3_1_0
                        ];
                    };
                };

            flake = {
                homeModules.default =
                    { config, pkgs, ... }:
                    {
                        imports = [ ];
                    };
            };
        };
}
