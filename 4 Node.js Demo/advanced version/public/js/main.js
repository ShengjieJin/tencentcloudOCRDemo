// 前端 JavaScript 代码
// 等待页面加载完成后执行代码
window.onload = function() {
	// 获取 input 元素和预览图片的 div 元素
	var inputFile = document.getElementById('image');
	var preview = document.getElementById('image-preview');

	// 给 input 元素添加 change 事件监听器
	inputFile.addEventListener('change', function() {
		// 获取选择的文件
		var file = this.files[0];

		// 创建 FileReader 对象
		var reader = new FileReader();

		// 当 FileReader 对象加载完成后执行以下代码
		reader.onload = function() {
            // 将选择的图片的 data URL 设置为预览图片的 src
			preview.src = reader.result;
		}

		// 读取选择的文件为 data URL
		reader.readAsDataURL(file);
	});
}


// 获取选择的图片路径并传递给后端 JavaScript 代码
function submitImage() {
	// 选中 input 标签
    const fileInput = document.getElementById("image");
	
    const selectedFile = fileInput.files[0];
    if (selectedFile) {
	  	// 使用 FormData 对象将文件包装成表单数据
      	const formData = new FormData();
      	formData.append("image", selectedFile);

		// 使用 AJAX 发送表单数据到后端
		const xhr = new XMLHttpRequest();
		xhr.open("POST", "/ocr", true);
		xhr.onload = () => {
		  if (xhr.status === 200) {
			text = xhr.responseText
			jsonData = JSON.parse(text)
			jsonString = JSON.stringify(jsonData.TableDetections, null, 2);

			console.log(jsonData);
			document.getElementById("json-output").innerText = jsonString;
		  } else {
			console.error(xhr.statusText);
		  }
		};
		xhr.onerror = () => {
		  console.error(xhr.statusText);
		};
		xhr.send(formData);
    }
  }
