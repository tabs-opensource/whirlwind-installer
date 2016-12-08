#!/bin/sh

# Copy plymouth theme folder into system.

SRC_DIR=/media/cdrom/oem/plymouth-theme/deepin-logo
DEST_DIR=/usr/share/plymouth/themes/deepin-logo
if [ -d "${SRC_DIR}" ]; then
  rm -rf "${DEST_DIR}" || warn_exit "Failed to remove old plymouth theme"
  cp -rf "${SRC_DIR}" "${DEST_DIR}" || warn_exit "Failed to copy plymouth theme to system"
  chmod +R 644 "${DEST_DIR}"
fi