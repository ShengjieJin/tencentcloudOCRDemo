package org.example;

import java.io.*;
import java.util.Base64;
import com.tencentcloudapi.common.Credential;
import com.tencentcloudapi.common.profile.ClientProfile;
import com.tencentcloudapi.common.profile.HttpProfile;
import com.tencentcloudapi.common.exception.TencentCloudSDKException;
import com.tencentcloudapi.ocr.v20181119.OcrClient;
import com.tencentcloudapi.ocr.v20181119.models.*;

public class RecognizeTableOCR {
    public static void main(String [] args) {
        try {
            // 读取图片文件
            String imagePath = "src/main/resources/images/1.jpg";
            File file = new File(imagePath);
            InputStream inputStream = new FileInputStream(file);
            byte[] buffer = new byte[(int) file.length()];
            inputStream.read(buffer);
            inputStream.close();

            // 将图片转换为 Base64 编码的字符串
            String imageBase64 = Base64.getEncoder().encodeToString(buffer);

            // 实例化一个认证对象
            Credential cred = new Credential("secretId", "secretKey");
            // 实例化一个http选项
            HttpProfile httpProfile = new HttpProfile();
            httpProfile.setEndpoint("ocr.tencentcloudapi.com");
            // 实例化一个client选项
            ClientProfile clientProfile = new ClientProfile();
            clientProfile.setHttpProfile(httpProfile);
            // 实例化要请求产品的client对象,clientProfile是可选的
            OcrClient client = new OcrClient(cred, "ap-guangzhou", clientProfile);
            // 实例化一个请求对象
            RecognizeTableOCRRequest req = new RecognizeTableOCRRequest();
            req.setImageBase64(imageBase64);
            // 返回的resp是一个RecognizeTableOCRResponse的实例，与请求对象对应
            RecognizeTableOCRResponse resp = client.RecognizeTableOCR(req);
            // 输出json格式的字符串回包
            System.out.println(RecognizeTableOCRResponse.toJsonString(resp));
        } catch (TencentCloudSDKException | IOException e) {
            System.out.println(e.toString());
        }
    }
}
