const addon = require("bindings")("file_attributes");

function setFileAttributes(filePath, modes) {
  return new Promise((resolve, reject) => {
    try {
      const modeList = modes.split(",");
      modeList.forEach((mode) => {
        addon.setFileAttributes(filePath, mode.trim());
      });
      resolve(true);
    } catch (error) {
      reject(error);
    }
  });
}

function getFileAttributes(filePath) {
  return new Promise((resolve, reject) => {
    try {
      const attributes = addon.getFileAttributes(filePath);
      resolve(attributes);
    } catch (error) {
      reject(error);
    }
  });
}

module.exports = {
  setFileAttributes,
  getFileAttributes,
};
