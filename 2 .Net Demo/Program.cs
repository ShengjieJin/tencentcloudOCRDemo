using System;
using System.Threading.Tasks;
using TencentCloud.Common;
using TencentCloud.Common.Profile;
using TencentCloud.Ocr.V20181119;
using TencentCloud.Ocr.V20181119.Models;

namespace TencentCloudExamples
{
    class RecognizeTableOCR
    {
        static void Main(string[] args)
        {
            try
            {
                // 实例化一个认证对象，入参需要传入腾讯云账户 SecretId 和 SecretKey，此处还需注意密钥对的保密
                Credential cred = new Credential {
                    SecretId = "SecretId",
                    SecretKey = "SecretKey"
                };
                // 实例化一个client选项，可选的，没有特殊需求可以跳过
                ClientProfile clientProfile = new ClientProfile();
                // 实例化一个http选项，可选的，没有特殊需求可以跳过
                HttpProfile httpProfile = new HttpProfile();
                httpProfile.Endpoint = ("ocr.tencentcloudapi.com");
                clientProfile.HttpProfile = httpProfile;

                // 实例化要请求产品的client对象,clientProfile是可选的
                OcrClient client = new OcrClient(cred, "ap-guangzhou", clientProfile);
                // 实例化一个请求对象,每个接口都会对应一个request对象
                RecognizeTableOCRRequest req = new RecognizeTableOCRRequest();
                // 将图片转换为base64编码
                byte[] imgBytes = File.ReadAllBytes("./images/1.jpg");
                string imgBase64 = Convert.ToBase64String(imgBytes);
                req.ImageBase64 = imgBase64;
                // 返回的resp是一个RecognizeTableOCRResponse的实例，与请求对象对应
                RecognizeTableOCRResponse resp = client.RecognizeTableOCRSync(req);
                // 输出json格式的字符串回包
                Console.WriteLine(AbstractModel.ToJsonString(resp));
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
            Console.Read();
        }
    }
}
            