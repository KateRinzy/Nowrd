I have this in @source/main.cc:
```cc
  InitWindow(800, 700, "nowrd");
  SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_BORDERLESS_WINDOWED_MODE);
```

However, I'm in a TWM, this means that
```cc
  InitWindow(800, 700, "nowrd");
```
forces the window to be float (if FLAG_BORDERLESS_WINDOWED_MODE is not present), how can i disable that behavior and let
the window be tiled by default?
