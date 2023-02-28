package main

import (
	"encoding/base64"
	"fmt"
	"io/ioutil"

	"github.com/tencentcloud/tencentcloud-sdk-go/tencentcloud/common"
	"github.com/tencentcloud/tencentcloud-sdk-go/tencentcloud/common/errors"
	"github.com/tencentcloud/tencentcloud-sdk-go/tencentcloud/common/profile"
	ocr "github.com/tencentcloud/tencentcloud-sdk-go/tencentcloud/ocr/v20181119"
)

func main() {
	// 读取本地图片文件
	fileData, err := ioutil.ReadFile("./images/1.jpg")
	if err != nil {
		panic(err)
	}
	// 将图片内容进行 Base64 编码
	imageBase64 := base64.StdEncoding.EncodeToString(fileData)

	// 实例化一个认证对象，入参需要传入腾讯云账户 SecretId 和 SecretKey，此处还需注意密钥对的保密
	credential := common.NewCredential(
		"SecretId",
		"SecretKey",
	)

	// 实例化一个client选项，可选的，没有特殊需求可以跳过
	cpf := profile.NewClientProfile()
	cpf.HttpProfile.Endpoint = "ocr.tencentcloudapi.com"

	// 实例化要请求产品的client对象,clientProfile是可选的
	client, err := ocr.NewClient(credential, "ap-guangzhou", cpf)
	if err != nil {
		panic(err)
	}

	// 实例化一个请求对象,每个接口都会对应一个request对象
	request := ocr.NewRecognizeTableOCRRequest()

	// 设置要识别的图片内容
	request.ImageBase64 = common.StringPtr(imageBase64)

	// 返回的resp是一个RecognizeTableOCRResponse的实例，与请求对象对应
	response, err := client.RecognizeTableOCR(request)
	if _, ok := err.(*errors.TencentCloudSDKError); ok {
		fmt.Printf("An API error has returned: %s", err)
		return
	}
	if err != nil {
		panic(err)
	}

	// 输出json格式的字符串回包
	fmt.Printf("%s", response.ToJsonString())
}
