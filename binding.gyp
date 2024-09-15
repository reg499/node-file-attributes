{
  "targets": [
    {
      "target_name": "file_attributes",
      "sources": [ "src/file_attributes.cc" ],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api').include\")"
      ]
    }
  ]
}
