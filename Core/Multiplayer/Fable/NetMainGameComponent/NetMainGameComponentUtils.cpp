#include "NetMainGameComponent.h"

void NetMainGameComponent::ClearInputBuffer() {
    std::cin.clear();

    while (_kbhit()) {
        (void)_getch();
    }
}
