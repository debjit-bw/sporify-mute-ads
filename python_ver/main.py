print("\n\nStarting...", end="")

import time, re
from pywinauto import Desktop
from pynput.keyboard import Key,Controller
keyboard = Controller()

state_scriptmuted = False
adtext="^Advertisement · Spotify - Audio playing.*"

def bar():
    i = 0
    while True:
        bar = list("-" * 50)
        bar[i%50] = '>'
        bar[(i+1)%50] = '>'
        bar[(i+2)%50] = '>'
        bar[(i+3)%50] = '>'
        bar[(i+4)%50] = '>'
        i += 1
        yield ''.join(bar)

print("\rRunning...         ")
prg = bar()
while True:
    flag = 0
    windows = Desktop(backend="uia").windows()
    is_ad = sum([len(re.findall("advertisement", w.window_text().lower()))>0 for w in windows])
    if is_ad>0 and state_scriptmuted!=True:
        keyboard.press(Key.media_volume_down)
        keyboard.release(Key.media_volume_down)
        keyboard.press(Key.media_volume_up)
        keyboard.release(Key.media_volume_up)
        keyboard.press(Key.media_volume_mute)
        keyboard.release(Key.media_volume_mute)
        state_scriptmuted = True
        print("\rMuted" + ' '*45)
        flag = 1
    if is_ad==0 and state_scriptmuted==True:
        keyboard.press(Key.media_volume_down)
        keyboard.release(Key.media_volume_down)
        keyboard.press(Key.media_volume_up)
        keyboard.release(Key.media_volume_up)
        state_scriptmuted = False
        print("\rUnmuted" + ' '*43)
        flag = 1
    if flag==0:
        print('\r' + next(prg), end = '')
    time.sleep(1)

