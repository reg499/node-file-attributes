const { setFileAttributes, getFileAttributes } = require(".././index");

// Suitable for Folders and Files.
const filePath = "test-file.txt";
const folderPath = "test-folder";

/* Hidden */
// setFileAttributes(filePath, "hide")
//   .then(() => console.log("File hidden successfully"))
//   .catch((err) => console.error("Error hiding file:", err));

/* Unhide */
// setFileAttributes(filePath, "show")
//   .then(() => console.log("File visibility restored successfully"))
//   .catch((err) => console.error("Error restoring file visibility:", err));

/* System */
// setFileAttributes(filePath, "system")
//   .then(() => console.log("File set as system successfully"))
//   .catch((err) => console.error("Error setting file as system:", err));

/* Remove system */
// setFileAttributes(filePath, "nosystem")
//   .then(() => console.log("File system attribute removed successfully"))
//   .catch((err) => console.error("Error removing file system attribute:", err));

/* Do both. (hidden, system) */
// setFileAttributes(filePath, "hide,system")
//   .then(() => console.log("File set as hidden and system successfully"))
//   .catch((err) =>
//     console.error("Error setting file as hidden and system:", err)
//   );

/* Remove both of them (hidden, system) */
// setFileAttributes(filePath, "show,nosystem")
//   .then(() => console.log("File attributes restored successfully"))
//   .catch((err) => console.error("Error restoring file attributes:", err));

/* Readonly */
// setFileAttributes(filePath, "readonly")
//   .then(() => console.log("File successfully set to read-only"))
//   .catch((err) => console.error("Error:", err));

/* Remove Readonly */
// setFileAttributes(filePath, "writable")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* Archive */
// setFileAttributes(filePath, "archive")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* Remove Archive */
// setFileAttributes(filePath, "noarchive")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* Temporary */
// setFileAttributes(filePath, "temporary")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* Remove Temporary */
// setFileAttributes(filePath, "temporary")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* Compress */
// setFileAttributes(filePath, "compress")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* Remove Compress */
// setFileAttributes(filePath, "nocompress")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* not indexed */
// setFileAttributes(filePath, "not_indexed")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* remove not indexed */
// setFileAttributes(filePath, "indexed")
//   .then(() => console.log("File attributes changed successfully"))
//   .catch((err) => console.error("Error:", err));

/* Make file normal (reset all properties) */
// setFileAttributes(filePath, "normal")
//   .then(() => console.log("File attributes reset to normal"))
//   .catch((err) => console.error("Error:", err));

/* Query file properties */
// getFileAttributes(filePath)
//   .then((attributes) => console.log("File attributes:", attributes))
//   .catch((err) => console.error("Error:", err));
