#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <vector>
#include <string>
#include <filesystem>

#include "fkps.h"

#define PARALELL_DET 8

std::string AddInToFname(std::string path_s, int n)
{
    auto path = std::filesystem::path(path_s);
    auto dir = path.parent_path();
    auto fname = path.stem();

    std::string s_fname = fname.string() + "_" + std::to_string(n) + path.extension().string();
    fname = dir / std::filesystem::path(s_fname);
    
    return fname.string();
}

int main(int argc, char* args[]) {

    if (argc != 4) {
        printf("Wrong number of arguments\n");
        return -1;
    }

    int toPart       = atoi(args[1]);
    int n            = atoi(args[2]);
    std::string path = std::string(args[3]);

    printf("Partitioning %d into %d, %d at a time.\n", toPart, n, PARALELL_DET);

    std::thread thread_v[PARALELL_DET];
    FakeProjectiveSpaces_t *fkps_v[PARALELL_DET];

    for (int i=0; i<PARALELL_DET; i++)
    {
        fkps_v[i] = FakeProjectiveSpacesInit(n, AddInToFname(path, i).c_str());
        if (fkps_v[i] == NULL) { printf("Could not initialize.\n"); return -2; }
        
        FakeProjectiveSpacesMatLoadRandom(fkps_v[i]);

        thread_v[i] = std::thread(&FakeProjectiveSpacesSolvePartial, fkps_v[i], (FkpsType_t) toPart);
    }

    for (int i=0; i<PARALELL_DET; i++)
    {
        thread_v[i].join();
        FakeProjectiveSpacesDeInit(fkps_v[i]);
    }

    return 0;   
}