#include <iostream> // std::cout
#include <fstream>  // std::fstream
#include <memory>

bool dump_str(std::fstream &jpg_file)
{
    uint16_t len;
    char two_byte_buf[2];
    jpg_file.read(two_byte_buf, sizeof(two_byte_buf));
    if (jpg_file.fail())
    {
        std::cout << "Cannot read from file\n";
        return false;
    }

    len = ((two_byte_buf[0] & 0xFF) << 8 | (two_byte_buf[1] & 0xFF)) & 0xFFFF;
    len -= 2;

    std::unique_ptr<char[]> str(new (std::nothrow) char[len + 1]());
    if (str == nullptr)
    {
        std::cout << "Cannot malloc memory\n";
        return false;
    }

    jpg_file.read(str.get(), len);
    if (jpg_file.fail())
    {
        std::cout << "Cannot read from file\n";
        return false;
    }
    str[len] = 0;
    printf("\tData(%d): %s\n", len, str.get());

    return true;
}

bool dummy_read_data(std::fstream &jpg_file)
{
    uint16_t len;
    char two_byte_buf[2];
    jpg_file.read(two_byte_buf, sizeof(two_byte_buf));
    if (jpg_file.fail())
    {
        std::cout << "Cannot read from file\n";
        return false;
    }

    len = ((two_byte_buf[0] & 0xFF) << 8 | (two_byte_buf[1] & 0xFF)) & 0xFFFF;
    len -= 2;
    printf("\tData(%d): \n", len);

    std::unique_ptr<char[]> data(new (std::nothrow) char[len]());
    if (data == nullptr)
    {
        std::cout << "Cannot malloc memory\n";
        return false;
    }

    jpg_file.read(data.get(), len);
    if (jpg_file.fail())
    {
        std::cout << "Cannot read from file\n";
        return false;
    }

    return true;
}

void jpeg_dump_header(const char *jpg_file_name)
{
    std::fstream jpg_file;
    char two_byte_buf[2];
    bool sos_found = false;
    bool eoi_found = false;

    jpg_file.open(jpg_file_name, std::fstream::in | std::fstream::binary);

    if (!jpg_file.is_open())
    {
        std::cout << "Cannot open file " << jpg_file_name;
        return;
    }

    while (!sos_found)
    {
        jpg_file.read(two_byte_buf, sizeof(two_byte_buf));
        if (jpg_file.fail())
        {
            std::cout << "Cannot read from file " << jpg_file_name;
            goto done;
        }
        // https://en.wikipedia.org/wiki/JPEG#Syntax_and_structure
        if ((two_byte_buf[0] & 0xFF == 0xff))
        {
            switch (two_byte_buf[1] & 0xFF)
            {
            case 0xC0:
                printf("Start Of Frame (baseline DCT): 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                dummy_read_data(jpg_file);
                break;
            case 0xC2:
                printf("Start Of Frame (progressive DCT): 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                dummy_read_data(jpg_file);
                break;
            case 0xC4:
                printf("Define Huffman Table: 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                dummy_read_data(jpg_file);
                break;

            case 0xD8:
                printf("Start of Image (SOI): 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                break;
            case 0xE0:
                printf("JFIF marker: 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                dump_str(jpg_file);
                break;
            case 0xE1:
            case 0xE2:
            case 0xE3:
            case 0xE4:
            case 0xE5:
            case 0xE6:
            case 0xE7:
            case 0xE8:
            case 0xE9:
            case 0xEA:
            case 0xEB:
            case 0xEC:
            case 0xED:
            case 0xEE:
                printf("EXIF marker: 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                dump_str(jpg_file);
                break;
            case 0xD0:
            case 0xD1:
            case 0xD2:
            case 0xD3:
            case 0xD4:
            case 0xD5:
            case 0xD6:
                printf("Restart: 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
            case 0xDA:
                printf("Start of Scan(SOS): 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                dummy_read_data(jpg_file);
                sos_found = true;
                break;
            case 0xDB:
                printf("Quantization tables: 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                dummy_read_data(jpg_file);
                break;
            case 0xDD:
                printf("Define Restart Interval(DRI): 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                dump_str(jpg_file);
                break;
            default:
                printf("Unknown: 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
                goto done;
            }
        }
        else
        {
            printf("Unknown: 0x%02X%02X\n", two_byte_buf[0] & 0xFF, two_byte_buf[1] & 0xFF);
            goto done;
        }
    }

    printf("SOS found at offset: %u\n", jpg_file.tellg());

    while (!eoi_found)
    {
        char c = jpg_file.get();
        if ((c & 0xff) == 0xff)
        {
            c = jpg_file.get();
            if ((c & 0xff) == 0xD9)
            {
                eoi_found = true;
                break;
            }
            // printf("Found 0xff but not EIO\n");
        }
        else if (c == -1)
        {
            printf("Cannot found at EIO\n");
            goto done;
        }
    }

    printf("EOI found at offset: %u\n", jpg_file.tellg());

    printf("\n");

done:
    jpg_file.close();
}

int main(int argc, char const *argv[])
{
    jpeg_dump_header(argv[1]);
    return 0;
}
