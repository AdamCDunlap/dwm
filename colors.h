#ifndef COLORS_H
#define COLORS_H
static const char colors[][ColLast][8] = {
   // border   foreground  background
   { "#444444", "#bbbbbb", "#222222" },  // 0 = normal
   { "#ffffff", "#eeeeee", "#005577" },  // 1 = selected
   { "#0066ff", "#0066ff", "#ffffff" },  // 2 = urgent/warning
   { "#ff0000", "#ffffff", "#ff0000" },  // 3 = error
};
#endif
