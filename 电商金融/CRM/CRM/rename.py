from PIL import Image
import os

def convert_and_rename_images(folder_path):
    # 获取指定文件夹中的所有图片文件
    image_files = [f for f in os.listdir(folder_path) if f.lower().endswith(('.png', '.jpg', '.jpeg'))]

    # 根据文件的修改时间进行排序
    image_files = sorted(image_files, key=lambda x: os.path.getmtime(os.path.join(folder_path, x)))

    # 确保文件夹路径以斜杠结尾
    if not folder_path.endswith('/'):
        folder_path += '/'

    # 遍历图片文件并转换格式、重命名
    for count, old_name in enumerate(image_files, start=1):
        # 生成新的文件名，使用6位数字格式
        new_name = f"{count:06d}.jpg"

        # 构造完整的文件路径
        old_path = os.path.join(folder_path, old_name)
        new_path = os.path.join(folder_path, new_name)

        # 打开 PNG/JPEG 图片并保存为 JPG
        image = Image.open(old_path)
        image = image.convert("RGB")
        image.save(new_path, "JPEG")

        # 删除原始文件
        os.remove(old_path)

if __name__ == "__main__":
    # 指定图片文件夹路径
    folder_path = "D:\Marston\课程作业及资料\电商金融\A-ERP-CRM-main\A-ERP-CRM-main\CRM\新建文件夹"

    # 调用函数进行转换和重命名
    convert_and_rename_images(folder_path)
