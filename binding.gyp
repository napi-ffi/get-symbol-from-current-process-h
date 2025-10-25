{
  "targets": [
    {
      "target_name": "test_symbol",
      "type": "executable",
      "sources": [
        "test/test.c"
      ],
      "include_dirs": [
        "include"
      ],
      "conditions": [
        ["OS!='win'", {
          "libraries": ["-ldl"]
        }]
      ]
    }
  ]
}
