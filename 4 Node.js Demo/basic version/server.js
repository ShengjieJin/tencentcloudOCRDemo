const tencentcloud = require("tencentcloud-sdk-nodejs");
const path = require("path");
const fs = require("fs");

// 导入 OCR 客户端
const OcrClient = tencentcloud.ocr.v20181119.Client;

// 设置密钥信息  
const clientConfig = {
  credential: {
    secretId: "yourSecretId",
    secretKey: "yourSecretKey",
  },
  region: "ap-guangzhou", // 设置请求地域
  profile: {
    httpProfile: {
      endpoint: "ocr.tencentcloudapi.com",
    },
  },
};

// 设置图片路径
const imagePath = path.join(__dirname, "images", "1.jpg");

// 实例化 OCR 客户端
const client = new OcrClient(clientConfig);

// 读取图片文件
let imageBase64;
try {
  imageBase64 = fs.readFileSync(imagePath, "base64");
} catch (err) {
  console.error(`Failed to read image file: ${err.message}`);
  return;
}

// 设置请求参数
const params = {
  ImageBase64: imageBase64, // 设置图片数据
};

// 发送 OCR 请求
client.RecognizeTableOCR(params)
  .then((data) => {
    console.log(data);
  })
  .catch((err) => {
    console.error(`OCR request failed: ${err.message}`);
  });
