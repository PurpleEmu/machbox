#ifdef __APPLE__
#error "Apple is vehemently anti-dev, and refuses to support modern OpenGL, OpenCL, or any Vulkan natively. Therefore, this software does not support MacOS or Apple."
#endif

#include "common.h"
#include "arm.h"
#include "iphone2g.h"
#include "iphone3gs.h"

enum class device_type
{
    iphone2g, iphone3gs
};

int main(int ac, char** av)
{
#ifdef __APPLE__
    printf("Really? You were smart enough to disable the first check, but still stupid enough to use an Apple operating system? Fucking shame on you, I'm out.\n");
    return -1;
#endif
    if(ac < 5)
    {
        printf("usage: %s [device] <path_to_bootrom> <path_to_nor> <path_to_iboot>\n", av[0]);
        printf("device can be \"iphone2g\", \"iphone2ghle\", \"iphone3gs\", or \"iphone3gshle\". No other devices are supported at this time.\n");
        return 1;
    }

    std::string device = av[1];
    device_type dev_type;
    bool bootromhle = false;
    if(device == "iphone2g")
    {
        dev_type = device_type::iphone2g;
        bootromhle = false;
    }
    else if(device == "iphone2ghle")
    {
        dev_type = device_type::iphone2g;
        bootromhle = true;
    }
    else if(device == "iphone3gs")
    {
        dev_type = device_type::iphone3gs;
        bootromhle = false;
    }
    else if(device == "iphone3gshle")
    {
        dev_type = device_type::iphone3gs;
        bootromhle = true;
    }
    else return 2;

    if(dev_type == device_type::iphone2g)
    {
        iphone2g* dev = (iphone2g*)malloc(sizeof(iphone2g));
        arm_cpu cpu;

        cpu.type = arm_type::arm11;

        cpu.init();

        dev->cpu = &cpu;

        dev->init();

        cpu.device = dev;
    
        cpu.rw_real = iphone2g_rw;
        cpu.ww_real = iphone2g_ww;

        FILE* fp = fopen(av[2],"rb");
        if(!fp)
        {
            printf("unable to open %s, are you sure it exists?\n", av[2]);
            return 3;
        }
        if(fread(dev->bootrom, 1, 0x10000, fp) != 0x10000)
        {
            fclose(fp);
            return 4;
        }
        fclose(fp);

        fp = fopen(av[3],"rb");
        if(!fp)
        {
            printf("unable to open %s, are you sure it exists?\n", av[3]);
            return 3;
        }
        if(fread(dev->nor, 1, 0x100000, fp) != 0x100000)
        {
            fclose(fp);
            return 4;
        }
        fclose(fp);

        if(bootromhle)
        {
            fp = fopen(av[4],"rb");
            if(!fp)
            {
                printf("unable to open %s, are you sure it exists?\n", av[3]);
                return 3;
            }
            fseek(fp, 0, SEEK_END);
            s64 filesize = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            if(filesize == -1)
            {
                fclose(fp);
                return 5;
            }
            if(fread(dev->iboot, 1, filesize, fp) != filesize)
            {
                fclose(fp);
                return 4;
            }
            fclose(fp);

            dev->init_hle();
        }
        else
        {
            memcpy(dev->lowram, dev->bootrom, 0x10000);
        }

        if(!bootromhle)
        {
            for(int i = 0; i < 40000; i++)
            {
                cpu.run(1);
                dev->tick();
            }
        }
        else
        {
            for(int i = 0; i < 300000; i++)
            {
                cpu.run(1);
                dev->tick();
            }
        }

        dev->exit();
        free(dev);
    }
    else if(dev_type == device_type::iphone3gs)
    {
        iphone3gs* dev = (iphone3gs*)malloc(sizeof(iphone3gs));
        arm_cpu cpu;

        cpu.type = arm_type::cortex_a8;

        cpu.init();

        dev->cpu = &cpu;

        dev->init();

        cpu.device = dev;
    
        cpu.rw_real = iphone3gs_rw;
        cpu.ww_real = iphone3gs_ww;

        FILE* fp = fopen(av[2],"rb");
        if(!fp)
        {
            printf("unable to open %s, are you sure it exists?\n", av[2]);
            return 3;
        }
        if(fread(dev->bootrom, 1, 0x10000, fp) != 0x10000)
        {
            fclose(fp);
            return 4;
        }
        fclose(fp);

        fp = fopen(av[3],"rb");
        if(!fp)
        {
            printf("unable to open %s, are you sure it exists?\n", av[3]);
            return 3;
        }
        if(fread(dev->nor, 1, 0x100000, fp) != 0x100000)
        {
            fclose(fp);
            return 4;
        }
        fclose(fp);


        for(int i = 0; i < 30000; i++)
        {
            cpu.run(1);
            dev->tick();
        }

        dev->exit();
        free(dev);
    }

    return 0;
}
