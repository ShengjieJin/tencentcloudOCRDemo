
#include <tencentcloud/core/Credential.h>
#include <tencentcloud/core/profile/ClientProfile.h>
#include <tencentcloud/core/profile/HttpProfile.h>
#include <tencentcloud/ocr/v20181119/OcrClient.h>
#include <tencentcloud/ocr/v20181119/model/RecognizeTableOCRRequest.h>
#include <tencentcloud/ocr/v20181119/model/RecognizeTableOCRResponse.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace TencentCloud;
using namespace TencentCloud::Ocr::V20181119;
using namespace TencentCloud::Ocr::V20181119::Model;
using namespace std;


static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; (i < 4); i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while ((i++ < 3))
      ret += '=';
  }

  return ret;
}



int main() {
        // 实例化一个认证对象，入参需要传入腾讯云账户 SecretId 和 SecretKey
        Credential cred = Credential("SecretId", "SecretKey");

        // 实例化一个http选项，可选的，没有特殊需求可以跳过
        HttpProfile httpProfile = HttpProfile();
        httpProfile.SetEndpoint("ocr.tencentcloudapi.com");

        // 实例化一个client选项，可选的，没有特殊需求可以跳过
        ClientProfile clientProfile = ClientProfile();
        clientProfile.SetHttpProfile(httpProfile);
        // 实例化要请求产品的client对象,clientProfile是可选的
        OcrClient client = OcrClient(cred, "ap-guangzhou", clientProfile);

        // 实例化一个请求对象,每个接口都会对应一个request对象
        RecognizeTableOCRRequest req = RecognizeTableOCRRequest();
        
        // 加载本地图片
        string image_path = "./images/1.jpg";
        ifstream in(image_path, ios::in | ios::binary);
        ostringstream oss;
        oss << in.rdbuf();
        string image_binary = oss.str();
        
        // 将二进制图像数据转换为Base64编码
        string image_base64 = base64_encode(reinterpret_cast<const unsigned char*>(image_binary.data()), image_binary.size());
        
        // 将Base64编码图像数据赋值到请求对象中
        req.SetImageBase64(image_base64);


        // 返回的resp是一个RecognizeTableOCRResponse的实例，与请求对象对应
        auto outcome = client.RecognizeTableOCR(req);
        if (!outcome.IsSuccess())
        {
            cout << outcome.GetError().PrintAll() << endl;
            return -1;
        }
        RecognizeTableOCRResponse resp = outcome.GetResult();
        // 输出json格式的字符串回包
        cout << resp.ToJsonString() << endl;
    
    return 0;
}
