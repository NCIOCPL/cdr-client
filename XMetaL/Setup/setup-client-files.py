#!/usr/bin/env python

"""Sets up the files needed to use CDR XMetaL.

The name of the installation directory reflects the fact that we are
currently using XMetaL 17.0.
"""

from logging import basicConfig, info, exception
from os import getenv
from pathlib import Path
from shutil import copy, copytree

# Find the XMetaL executable.
def find_xmetal():
    names = "ProgramFiles(x86)", "ProgramFiles", "ProgramW6432"
    for name in names:
        value = getenv(name)
        if value:
            path = Path(value, "XMetaL 17.0", "Author", "xmetal.exe")
            if path.exists():
                print(f"Found {path}.")
                return path.parent
    print("XMetaL is not installed.")
    input("Press Return to abort ... ")
    exit(1)


# Establish locations for everything.
SOURCE = Path(__file__).parent.resolve() / "ClientFiles"
APPDATA = Path(getenv("APPDATA"))
USER_PROFILE = Path(getenv("USERPROFILE"))
DESKTOP = USER_PROFILE / "Desktop"
DOCUMENTS = USER_PROFILE / "Documents"
CLIENT_DIR = APPDATA / "SoftQuad" / "XMetaL" / "17.0"
XMETAL_INI = CLIENT_DIR / "XMetaL.ini"
XMETAL_INI_ORIGINAL = CLIENT_DIR / "XMetaL.ini.original"
ICONS = CLIENT_DIR / "Icons"
ICONS_INI = ICONS / "icons.ini"
LOGPATH = CLIENT_DIR / "logs"
LOGFILE = LOGPATH / "setup.log"
XMETAL = find_xmetal()
XMETAL_ICONS = XMETAL / "Icons"
XMETAL_AUTHOR = "XMetaL Author"
LOADER = "cdr-loader.pyw"
SHORTCUT = "shortcut"
CDR_LNK = "CDR.lnk"
SHORTCUT_PATH = DESKTOP / CDR_LNK
CDR_ICO = "cdr.ico"
INSTRUCTIONS = f"""
CDR XMetaL is now ready to use. Double-click on the CDR desktop shortcut to
launch XMetaL, and if asked for the location of the licence file, navigate
to the {CLIENT_DIR} directory.
"""

# Create the customized settings file.
XMETAL_SETTINGS = f"""\
ai_sort_attr = false
ai_sort_type =
draw_grid_on_borderless_tables = true
file_dialog_last_location =
folder_dialog_last_location =
hide_tag_text = false
parser_lax_empty_content = false
restore_last_open_docs = false
source_view_auto_indent = false
source_view_use_tabs = false
draw_grid_on_borderless_tables = true
save_path = {CLIENT_DIR}\Cdr\ReadOnly
document_path = {CLIENT_DIR}\Cdr\ReadOnly
macro_file = {CLIENT_DIR}\Macros\cdr.xml
macro_path = {CLIENT_DIR}\Macros
rules_path = {CLIENT_DIR}\Rules
tbr_path = {CLIENT_DIR}\Rules
styles_path = {CLIENT_DIR}\Display
templates_path = {CLIENT_DIR}\Template
toolbar_icon_path = {CLIENT_DIR}\Icons
hide_track_changes = false
QUICKMARKUP_ASSISTANT = stopped
"""

# Tell the operator what we're doing.
print(f"Installing from {SOURCE}")
print(f"Installing to {CLIENT_DIR}")
input("Press Enter to continue, or Control-C to abort.")

# Set up logging.
try:
    LOGPATH.mkdir(exist_ok=True, parents=True)
except Exception as e:
    print(f"Unable to create {LOGPATH}: {e}")
    input("Press Enter to quit ... ")
    exit(1)
format = "%(asctime)s [%(levelname)s] %(message)s"
basicConfig(filename=LOGFILE, format=format, level="INFO")
info("Installing from %s", SOURCE)
info("Installing to %s", CLIENT_DIR)

# Install the icon files.
print("Installing icon files.")
info("Installing icons into %s", ICONS)
try:
    copytree(XMETAL_ICONS, ICONS, dirs_exist_ok=True)
    if ICONS_INI.exists():
        ICONS_INI.unlink()
except Exception as e:
    exception("Failure installing icons")
    print(f"Unable to install icons: {e}")
    input("Press Enter to quit ... ")
    exit(1)

# Install the settings file.
print("Installing settings file.")
info("Replacing %s", XMETAL_INI)
try:
    if XMETAL_INI.exists():
        XMETAL_INI.chmod(0o777)
        if XMETAL_INI_ORIGINAL.exists():
            XMETAL_INI.unlink()
        else:
            XMETAL_INI.rename(XMETAL_INI_ORIGINAL)
    XMETAL_INI.write_text(XMETAL_SETTINGS)
except Exception as e:
    exception("Failure installing settings")
    print(f"Unable to install settings: {e}")
    input("Press Enter to quit ... ")
    exit(1)

# Install the loader.
source = SOURCE / LOADER
target = CLIENT_DIR / LOADER
print("Installing the CDR launch file.")
info("Installing %s", target)
try:
    copy(source, target)
except Exception as e:
    exception("Failure installing %s", target)
    print(f"Failure installing {LOADER}: {e}")
    input("Press Enter to quit ... ")
    exit(1)

# Copy the CDR icon.
source = SOURCE / CDR_ICO
target = CLIENT_DIR / CDR_ICO
print("Installing the CDR icon file.")
info("Installing %s", target)
try:
    copy(source, target)
except Exception as e:
    exception("Failure installing %s", target)
    print(f"Failure installing {CDR_ICO}: {e}")
    input("Press Enter to quit ... ")
    exit(1)

# Install the desktop shortcut.
print("Installing the Desktop shortcut.")
source = SOURCE / SHORTCUT
target = DESKTOP / CDR_LNK
info("Installing %s", target)
try:
    shortcut_bytes = source.read_bytes()
    target.write_bytes(shortcut_bytes)
except Exception as e:
    exception("Failure installing %s", target)
    print(f"Failure installing {target}: {e}")
    input("Press Enter to quit ... ")
    exit(1)

# Move the XMetaL shortcut.
print("Moving the original XMetaL shortcut.")
filename = f"{XMETAL_AUTHOR}.lnk"
source = DESKTOP / filename
destination = DOCUMENTS / filename
if source.exists():
    info("Moving %s", source)
    try:
        source.rename(destination)
    except:
        info("Failure moving %s (removing instead)", source)
        try:
            source.unlink()
        except:
            exception("Failure removing %s", source)

# That's all, folks!
print(INSTRUCTIONS)
info("Setup completed successfully.")
input("Press Enter to close ... ")
