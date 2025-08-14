# KOSP Window
This is a part of a paid product named KOSP Project, a sound pack created in
FMOD for the ToLiss A32X series.  
The specific repository contains a C plugin of a window.

You can purchase the sound product here: https://store.x-plane.org/KOSP-PROJECT--A319-A320-A321-Full-Soundscape_p_1773.html


![Menus](https://github.com/squeakyparrot/kosp_window/blob/main/img/menus.png)

The menu is a fancy toy that comes with the soundscape for users to customise.
As I am selling sounds and not plugins, this plugin is and will remain public. 

## Build
NOTE: As far as this is concerned it only builds on Ubuntu 22 LTS due to
specific requirements from libacfutils.

Step 1: Head into the repository and clone submodules.
```bash
git submodule update --init --recursive
```

Step 2: Build libacfutils
```bash
cd lib/libacfutils
./build_deps
./build_redist
```

Step 3: Build our Plugin
```bash
cd -
./BuildPlugin
```

## Special Thanks
@skiselkov For libacfutils  
@amyinorbit For windows cross-compile scripts