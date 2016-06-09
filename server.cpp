
#include <d3dcompiler.h>

#include <string>

#include <cstdio>
#include <cstdint>

int main(void)
{
    ID3DBlob *shader_blob, *error_blob;

    HMODULE lib = LoadLibrary("d3dcompiler_47.dll");
    pD3DCompile compile = (pD3DCompile)GetProcAddress(lib, "D3DCompile");

    std::string shader_source, shader_file, shader_main, shader_type;
    uint32_t flags = 0;
    HRESULT ret = 0;

    bool must_reset = true;

    for (;;)
    {
        if (must_reset)
        {
            shader_source = shader_file = shader_main = shader_type = "";
            shader_blob = error_blob = nullptr;
            must_reset = false;
            flags = 0;
            ret = 0;
        }

        std::string tmp;
        int ch = getchar();

        if (ch < 0)
            break;

        switch (ch)
        {
        case 's':
            while ((ch = getchar()))
                shader_source += ch;
            break;

        case 'f':
            while ((ch = getchar()))
                shader_file += ch;
            break;

        case 'F':
            while ((ch = getchar()))
                tmp += ch;
            flags = atoi(tmp.c_str());
            break;

        case 'm':
            while ((ch = getchar()))
                shader_main += ch;
            break;

        case 't':
            while ((ch = getchar()))
                shader_type += ch;
            break;

        case 'X':
            ret = compile(shader_source.c_str(), shader_source.size(),
                          shader_file.c_str(),
                          nullptr, /* unimplemented */
                          nullptr, /* unimplemented */
                          shader_main.c_str(),
                          shader_type.c_str(),
                          flags, 0, &shader_blob, &error_blob);
            fprintf(stdout, "r%d%c", (int)ret, '\0');
            if (shader_blob)
            {
                fprintf(stdout, "l%d%c", (int)shader_blob->GetBufferSize());
                fwrite(shader_blob->GetBufferPointer(), (int)shader_blob->GetBufferSize(), 1, stdout);
                shader_blob->Release();
            }
            break;
        }
    }
}

