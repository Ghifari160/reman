# ReMan

ReMan is a project release manager. The idea is that release distribution archives will be packaged
identically for all projects. The packager (`package`) handles this process. Different tech stacks
(NodeJS + Express, React web apps, C++ projects, Java projects, etc.) have their own compilation
and build procedures. Tech stack-specific builders (not yet implemented) handle this process. Some
projects have their own specific compilation and build procedures. Project-specific builders
(i.e. `build-crashpad`) handle this process. The build pipeline is as follows:

Project-specific

``` text
project-specific builder -> packager
```

Tech Stack-specific

``` text
tech stack-specific builder -> packager
```

## Included Tools

- Crashpad Container Generator
- Crashpad Builder
- Packager

## Installation

Clone from the Git repository and enter the directory

``` shell
git clone https://github.com/ghifari160/reman
cd reman
```

Run the installation script

``` shell
./install.sh
```

Add the ReMan installation directory to the user `PATH` and set `REMAN_DIR` to the ReMan root
directory. In Linux, you normally append this line to `~/.bashrc` or `~/.profile`. In macOS, you
normally append it to `~/.bash_profile`

``` bash
export PATH=/path/to/reman/binary:$PATH
export REMAN_DIR=/path/to/reman/root
```

## Usage

### Crashpad Container Generator

Run the tool

``` shell
gencontainer-crashpad
```

### Crashpad Builder

Declare the packaging tool, packaging directory, project name, and project version. You can append
the distribution platorm to the project name.

``` shell
export PACKAGER=packager
export PACKAGER_TARGET=$PWD/out/Release
export PACKAGER_PROJECT=crashpad-macos
export PACKAGER_PROJECT_VERSION=0.8.0
```

Run the tool

``` shell
build-crashpad
```

#### Variables

| Variable                   | Explanation                                                                                        |
|----------------------------|----------------------------------------------------------------------------------------------------|
| `PACKAGER`                 | Path to ReMan packaging tool                                                                       |
| `PACKAGER_TARGET`          | Packaging target directory. Distribution packages will be stored here                              |
| `PACKAGER_PROJECT`         | Project name. You may append the distribition platform to the project name (i.e. `crashpad-macos`) |
| `PACKAGER_PROJECT_VERSION` | Project version                                                                                    |

### Packager

Enter the prepared directory

``` shell
cd build
```

Run the build tool

``` shell
package /target/directory projectname project version
```
