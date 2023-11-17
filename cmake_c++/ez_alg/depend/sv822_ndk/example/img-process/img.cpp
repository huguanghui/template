#include <VX/vx.h>
#include <vx_log.h>
#include <net_api.h>
#include <memory.h>

int main()
{
    FILE * fin;
    int flen;

    //create context
	vx_context context = vxCreateContext();
	ERROR_CHECK_OBJECT(context);

    //malloc yuv buffer
    int src_w = 960;
    int src_h = 640;
    vx_size src_handle = AllocDeviceImageBuffer(context, YUV420_SP, src_w, src_h);
    if (src_handle == 0) {
        VX_LOG("alloc yuv image buffer error.\n");
        return -1;
    }
    vx_size src_phys_addr = vxGetDeviceMemoryPhysicalAddress(src_handle);
	vx_size src_virt_addr = vxGetDeviceMemoryVirtualAddress(src_handle);

    fin = fopen("orange_y.bin", "rb");
    fseek(fin, 0, SEEK_END);
    flen = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    fread((void*)src_virt_addr, 1, flen, fin);
    fclose(fin);

    fin = fopen("orange_uv.bin", "rb");
    fseek(fin, 0, SEEK_END);
    flen = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    fread((void*)(src_virt_addr + src_w * src_h), 1, flen, fin);
    fclose(fin);

    //flush cache
    vxFlushDeviceMemoryCache(context, src_handle);

    //malloc rgba buffer
    int dst_w = 224;
    int dst_h = 224;
    vx_size dst_handle = AllocDeviceImageBuffer(context, NNA_BGRA, dst_w, dst_h);
    if (dst_handle == 0) {
        VX_LOG("alloc rgba image buffer error.\n");
        return -1;
    }
	vx_size dst_virt_addr = vxGetDeviceMemoryVirtualAddress(dst_handle);
    vx_size dst_img_size = vxGetDeviceMemorySize(dst_handle);

    //config image convert
    img_cvt_param param;
    param.input_fmt = YUV420_SP;
    param.input_width = src_w;
    param.input_height = src_h;
    param.roi_in_x = 0;
    param.roi_in_y = 0;
    param.roi_in_w = src_w;
    param.roi_in_h = src_h;
    param.input_color_range = 0;
    param.output_fmt = NNA_BGRA;
    param.output_width = dst_w;
    param.output_height = dst_h;
    param.crop_out_x = 7;
    param.crop_out_y = 16;
    param.crop_out_w = 200;
    param.crop_out_h = 208;
    ImageConvert(context, &param, src_phys_addr, src_phys_addr + src_w * src_h, dst_handle);
    vxInvalidateDeviceMemoryCache(context, dst_handle);

    //dump
    fin = fopen("img.bin", "wb");
    fwrite((void*)dst_virt_addr, 1, dst_img_size, fin);
    fclose(fin);

    //revert to no-aligned data
    vx_uint8 * revert_data = (vx_uint8*)malloc(dst_w * dst_h * 3);
    RgbImageRevert(dst_w, dst_h, (vx_uint8*)dst_virt_addr, HWC, revert_data);
    fin = fopen("revert_img.bin", "wb");
    fwrite(revert_data, 1, dst_w * dst_h * 3, fin);
    fclose(fin);

    //convert to aligned data
    memset((void*)dst_virt_addr, 0, dst_img_size);
    RgbImageConvert(dst_w, dst_h, HWC, revert_data, (vx_uint8*)dst_virt_addr);
    fin = fopen("convert_img.bin", "wb");
    fwrite((void*)dst_virt_addr, 1, dst_img_size, fin);
    fclose(fin);

    free(revert_data);
    FreeDeviceImageBuffer(context, dst_handle);
    FreeDeviceImageBuffer(context, src_handle);
    ERROR_CHECK_STATUS(vxReleaseContext(&context));

    return 0;
}