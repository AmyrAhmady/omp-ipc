const fs = require("fs");
const path = require("path");

const getLineBreakType = (content) => {
  const indexOfLF = content.indexOf("\n", 1);

  if (indexOfLF === -1) {
    if (content.indexOf("\r") !== -1) return "\r";
    return "\n";
  }

  if (content[indexOfLF - 1] === "\r") return "\r\n";
};

const getDataTypeForDocs = (type) => {
  switch (type) {
    case "int":
      return "int";
    case "ConstStringRef":
      return "string";
    case "StringRef":
      return "string";
    case "bool":
      return "bool";
    case "float":
      return "float";
    case "uintptr_t":
      return "pointer";
    case "uint8_t":
      return "uint8";
    case "uint32_t":
      return "uint32";
    default:
      throw `Error converting type: can not convert ${type}`;
  }
};

const files = fs.readdirSync("./src/api/scripting", { recursive: true });
files.forEach((file) => {
  if (file.includes("APIs.cpp")) {
    const filePath = path.join("./src/api/scripting", file);
    const apiFilePath = path.join("./apidocs", `${path.dirname(file)}.json`);
    const api = fs.existsSync(apiFilePath)
      ? JSON.parse(fs.readFileSync(apiFilePath).toString())
      : {};

    api.functions = [];

    const content = fs.readFileSync(filePath).toString();

    const regex =
      getLineBreakType(content) === "\n"
        ? /IPC_API\((.*?)\)\n\{\n([\S\s]*?)\n\}\n\n/gm
        : /IPC_API\((.*?)\)\r\n\{\r\n([\S\s]*?)\r\n\}\r\n\r\n/gm;

    let m;
    while ((m = regex.exec(content)) !== null) {
      if (m.index === regex.lastIndex) {
        regex.lastIndex++;
      }

      if (m.length === 3) {
        const apiDefParams = m[1].split(", ");
        const funcName = apiDefParams[0];

        apiDefParams.shift();
        const params = apiDefParams.map((paramWithType) => {
          const p = paramWithType.split(" ");
          return { name: p[1], type: getDataTypeForDocs(p[0]) };
        });

        let returnValues = [];

        const regex = /IPC_RETURN\((.*?)\);/gm;

        let n;
        while ((n = regex.exec(m[0])) !== null) {
          if (n.index === regex.lastIndex) {
            regex.lastIndex++;
          }

          if (n.length == 2) {
            const returns = n[1].split(", ");
            if (returns[0] !== "") {
              returnValues = returns.map((returnWithType) => {
                const p = returnWithType.split(" ");
                return { name: p[1], type: getDataTypeForDocs(p[0]) };
              });
            }
          }
        }

        api.functions.push({
          name: funcName,
          params: params,
          return: returnValues,
        });
      }
    }

    fs.writeFileSync(apiFilePath, JSON.stringify(api, undefined, 2));
  }
});
