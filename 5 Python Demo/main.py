import json
import base64
from PIL import Image
from io import BytesIO
from tencentcloud.common import credential
from tencentcloud.common.profile.client_profile import ClientProfile
from tencentcloud.common.profile.http_profile import HttpProfile
from tencentcloud.common.exception.tencent_cloud_sdk_exception import TencentCloudSDKException
from tencentcloud.ocr.v20181119 import ocr_client, models

# 读入图片并编码为base64
with open("./images/1.jpg", "rb") as image_file:
    # 打开图片并转换为PIL Image对象
    image = Image.open(image_file)

    # 将PIL Image对象转换为BytesIO对象
    buffer = BytesIO()
    image.save(buffer, format='JPEG')

    # 将BytesIO对象中的数据读取为二进制数据，并使用base64编码
    img_base64 = base64.b64encode(buffer.getvalue()).decode('utf-8')

try:
    # 实例化一个认证对象，入参需要传入腾讯云账户 SecretId 和 SecretKey
    cred = credential.Credential("SecretId", "SecretKey")

    # 实例化一个http选项，可选的，没有特殊需求可以跳过
    httpProfile = HttpProfile()
    httpProfile.endpoint = "ocr.tencentcloudapi.com"

    # 实例化一个client选项，可选的，没有特殊需求可以跳过
    clientProfile = ClientProfile()
    clientProfile.httpProfile = httpProfile

    # 实例化要请求产品的client对象,clientProfile是可选的
    client = ocr_client.OcrClient(cred, "ap-guangzhou", clientProfile)

    # 实例化一个请求对象,每个接口都会对应一个request对象
    req = models.RecognizeTableOCRRequest()
    params = {
        "ImageBase64": img_base64,  # 将图片的base64格式字符串传递给API
    }
    req.from_json_string(json.dumps(params))

    # 返回的resp是一个RecognizeTableOCRResponse的实例，与请求对象对应
    resp = client.RecognizeTableOCR(req)

    # 输出json格式的字符串回包
    print(resp.to_json_string())

except TencentCloudSDKException as err:
    print(err)
