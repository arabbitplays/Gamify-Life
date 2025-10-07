#include <iostream>
#include <memory>

#include "Profile.hpp"
#include "view/IFrontend.hpp"
#include "view/not_curses/NotCursesFrontend.hpp"

int main(int argc, char *argv[]) {
    const auto profile = std::make_shared<Profile>("Oschdi");
    const auto task1 = std::make_shared<Task>("Stretching", 5);
    profile->addDoneTaskToday(task1);
    //profile->printDoneTasks();

    /*// Print table rows
    for (const auto& p : tasks) {
        ncplane_printf(std_plane, "%-15s %3f\n", p.getName().c_str(), p.getScore());
    }
    notcurses_render(nc);*/

    FrontendHandle frontend = std::make_shared<NotCursesFrontend>();
    frontend->init();
    frontend->run();
    frontend->stop();

    return 0;
}
