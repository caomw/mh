#include "gui/meshviewer.h"

using namespace mh;

int main(int argc, char* argv[])
{
    MeshViewer viewer;

    while (!viewer.shouldClose())
    {
        viewer.makeCurrent();
        viewer.mainLoop();
        viewer.swap();
    }

    glfwTerminate();
    
    return 0;
}
