// main.cpp

// plz remember
//
// x -> lines
// y -> columns
//
// "ncurses.h" shits are reversed
// it's (y, x) not (x, y)

#include <iostream>
#include <ncurses.h>
#include "./powermgr/power.h"

void finish(WINDOW* mainw, WINDOW* shadoww) {
    nocbreak();
    curs_set(2);
    echo();
    delwin(mainw);
    delwin(shadoww);

    endwin();
}

int main() {
    initscr();
    cbreak();
    curs_set(0);
    noecho();

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_MAGENTA);   // background
    init_pair(2, COLOR_BLACK, COLOR_WHITE);     // dialog background + text
    init_pair(3, COLOR_WHITE, COLOR_BLACK);     // dialog text selected
    init_pair(4, COLOR_BLACK, COLOR_BLACK);     // dialog shadow

    bool active = true;
    unsigned char selected = 0;
    unsigned char max_select = 3;
    bool sync_enabled = true;
    unsigned char invoked_action = 0;

    wbkgd(stdscr, COLOR_PAIR(1));
    wrefresh(stdscr);

    unsigned short max_width = getmaxx(stdscr);
    unsigned short max_height = getmaxy(stdscr);

    int window_width = 48;
    int window_height = 8;

    int window_start_x = ((max_width / 2) - (window_width / 2));
    int window_start_y = ((max_height / 2) - (window_height / 2));

    WINDOW* shadowindow = newwin(
        window_height,
        window_width,
        (window_start_y + 1),
        (window_start_x + 1)
    );

    wbkgd(shadowindow, COLOR_PAIR(4));
    wrefresh(shadowindow);

    WINDOW* mainwindow = newwin(
        window_height,
        window_width,
        window_start_y,
        window_start_x
    );

    keypad(mainwindow, TRUE);

    box(mainwindow, 0, 0);
    wbkgd(mainwindow, COLOR_PAIR(2));
    wrefresh(mainwindow);

    wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
    mvwprintw(mainwindow, 1, 1, "Choose what you want to do with the kernel    ");
    mvwprintw(mainwindow, 2, 1, "system power. Syncing is highly recommended.  ");
    wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);

    wrefresh(mainwindow);

    while (active)
    {
        if (selected == 0) {
            wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(3)), NULL);
            mvwprintw(mainwindow, 6, 1, "[ Cancel ]");
            wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(3)), NULL);
        } else {
            wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
            mvwprintw(mainwindow, 6, 1, "[ Cancel ]");
            wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
        }

        if (selected == 1) {
            wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(3)), NULL);
            if (sync_enabled) {
                mvwprintw(mainwindow, 4, 4, "[x] Perform file system sync");
            } else {
                mvwprintw(mainwindow, 4, 4, "[ ] Perform file system sync");
            }
            wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(3)), NULL);
        } else {
            wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
            if (sync_enabled) {
                mvwprintw(mainwindow, 4, 4, "[x] Perform file system sync");
            } else {
                mvwprintw(mainwindow, 4, 4, "[ ] Perform file system sync");
            }
            wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
        }

        if (selected == 2) {
            wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(3)), NULL);
            mvwprintw(mainwindow, 6, 21, "[ Restart ]");
            wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(3)), NULL);
        } else {
            wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
            mvwprintw(mainwindow, 6, 21, "[ Restart ]");
            wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
        }

        if (selected == 3) {
            wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(3)), NULL);
            mvwprintw(mainwindow, 6, 33, "[ Power Off ]");
            wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(3)), NULL);
        } else {
            wattr_on(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
            mvwprintw(mainwindow, 6, 33, "[ Power Off ]");
            wattr_off(mainwindow, static_cast<attr_t>(COLOR_PAIR(2)), NULL);
        }

        wrefresh(mainwindow);
        

        int character = wgetch(mainwindow);
        // \t
        if (character == 9) {
            int next = (selected + 1);
            if (next > max_select) {
                selected = 0;
            } else {
                selected = next;
            }
        // KEY_ENTER, \n, \r
        } else if (character == KEY_ENTER || character == 10 || character == 13) {
            if (selected == 0)
            {
                finish(mainwindow, shadowindow);
                break;
            }
            else if (selected == 1)
            {
                sync_enabled = !sync_enabled;
            }
            else if (selected == 2)
            {
                invoked_action = 1;

                finish(mainwindow, shadowindow);
                break;
            } else if (selected == 3) {
                invoked_action = 2;

                finish(mainwindow, shadowindow);
                break;
            }
            
        }
    }

    switch (invoked_action)
    {
    case 1:
        std::cout << "Restart initiated.\nSync: " << sync_enabled << "\n";
        power::sysreboot(sync_enabled);
        break;

    case 2:
        std::cout << "Power off initiated.\nSync: " << sync_enabled << "\n";
        power::syspoweroff(sync_enabled);
        break;
    
    default:
        std::cout << "Canceled.\n";
        break;
    }

    return 0;
}