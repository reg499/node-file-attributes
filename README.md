# File Attributes Manager - Node.js Addon

**File Attributes Manager** is a Node.js native addon built with C++ for managing file attributes on Windows. It provides a simple interface to set and query various file attributes like hidden, system, read-only, archive, compression, indexing, and more. This addon leverages Windows APIs to interact with file attributes at the OS level, offering more control and precision than what is typically available in standard Node.js modules.

## Features

- **Set file as hidden or visible** (`hide`, `show`)
- **Mark file as system** or remove system attribute (`system`, `nosystem`)
- **Set file as read-only** or make it writable (`readonly`, `writable`)
- **Archive flag management** (`archive`, `noarchive`)
- **Temporary file flag management** (`temporary`, `notemporary`)
- **Set file to normal** (resets all custom attributes)
- **Enable NTFS compression** or remove it (`compress`, `nocompress`)
- **Control content indexing** (`not_indexed`, `indexed`)
- **Multiple attributes** can be applied at once (`e.g., hide,readonly`)
- **Query file attributes** in JSON format

## Installation

Before installing the package, make sure you have Node.js and npm installed on your machine.

To install the package, run the following command:

```bash
npm install node-file-attributes
```

> **Note**: This module works only on **Windows** platforms.

### Prerequisites

- **Node.js**: Ensure you have Node.js installed. The addon is built using Node.js native addons (C++).
- **Windows OS**: The file attribute management is based on Windows-specific APIs, so this module will only work on Windows environments.

## Usage

Once installed, you can start using the module by importing it into your project. Below are some common examples of how to use the module.

### Importing the Module

```javascript
const {
  setFileAttributes,
  getFileAttributes,
} = require("node-file-attributes");
```

### Setting File Attributes

You can use the `setFileAttributes()` function to set various attributes on a file or folder. The function supports multiple attributes at once.

```javascript
const filePath = "path/to/your/file.txt";

// Hide and set the file as read-only
setFileAttributes(filePath, "hide,readonly")
  .then(() => console.log("Attributes set successfully"))
  .catch((err) => console.error("Error:", err));
```

### Querying File Attributes

To query the current attributes of a file, use the `getFileAttributes()` function. It returns a JSON object showing the status of different attributes.

```javascript
getFileAttributes(filePath)
  .then((attributes) => console.log("File attributes:", attributes))
  .catch((err) => console.error("Error querying file attributes:", err));
```

The response will be a JSON object like this:

```json
{
  "hidden": true,
  "system": false,
  "readonly": true,
  "archive": true,
  "temporary": false,
  "not_indexed": false
}
```

### Available Modes

You can set the following modes using the `setFileAttributes()` function:

| Mode          | Description                                   |
| ------------- | --------------------------------------------- |
| `hide`        | Marks the file as hidden                      |
| `show`        | Makes the file visible (removes hidden flag)  |
| `system`      | Marks the file as a system file               |
| `nosystem`    | Removes the system file flag                  |
| `readonly`    | Sets the file as read-only                    |
| `writable`    | Removes the read-only flag                    |
| `archive`     | Marks the file as archived                    |
| `noarchive`   | Removes the archive flag                      |
| `temporary`   | Marks the file as temporary                   |
| `notemporary` | Removes the temporary flag                    |
| `compress`    | Enables NTFS compression                      |
| `nocompress`  | Disables NTFS compression                     |
| `not_indexed` | Prevents the file from being indexed          |
| `indexed`     | Allows the file to be indexed                 |
| `normal`      | Resets all attributes (makes the file normal) |

You can also pass multiple modes as a comma-separated list, e.g., `"hide,readonly"`.

## Example Code

Here are some more examples of using the module to set different attributes:

```javascript
const filePath = "test-file.txt";

/* Set the file as hidden */
setFileAttributes(filePath, "hide")
  .then(() => console.log("File is now hidden"))
  .catch((err) => console.error("Error:", err));

/* Remove the hidden attribute */
setFileAttributes(filePath, "show")
  .then(() => console.log("File is now visible"))
  .catch((err) => console.error("Error:", err));

/* Set the file as read-only */
setFileAttributes(filePath, "readonly")
  .then(() => console.log("File is now read-only"))
  .catch((err) => console.error("Error:", err));

/* Remove the read-only attribute */
setFileAttributes(filePath, "writable")
  .then(() => console.log("File is now writable"))
  .catch((err) => console.error("Error:", err));

/* Query current file attributes */
getFileAttributes(filePath)
  .then((attributes) => console.log("File attributes:", attributes))
  .catch((err) => console.error("Error:", err));
```

## Building from Source

If you want to build the addon from the source code, you can clone the repository and run the following commands:

```bash
# Install dependencies
npm install

# Build the addon
npm run build
```

This will compile the C++ code and generate the necessary bindings for Node.js.

## Contributing

Contributions are welcome! If you encounter any issues, feel free to create a GitHub issue or submit a pull request. Make sure to follow the coding standards and best practices when contributing.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
