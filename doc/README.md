# YAUI

---

## EngineN

var/func|access|abstract|parameters|return|functionality|threading
-|-|-|-|-|-|-
mTasks|private|-|-|-|FIFO queue|thread-safe
addTask()|public|no|task:Functor|bool|adds Task to mTasks|thread-safe
handleTask()|private|no|task:Functor|bool|handles tasks one by one|single threaded
initializeEngineN()|public|no|-|bool|intializes EventDispatcher, ViewManager|-
start()|public|no|-|bool|starts the engine|blocking

---

## Event

- Event::Mouse
    - LEFT_DOWN
    - LEFT_UP
    - LEFT_CLICK
    - RIGHT_DOWN
    - RIGHT_UP
    - RIGHT_CLICK
    - CURSOR_HOVER

- Event::Keyboard
    - KEY_DOWN
    - KEY_UP
    - KEY_PRESS

var/func|access|abstract|parameters|return|functionality|threading
-|-|-|-|-|-|-
mMouseEvent|private|-|-|-|Event::Mouse|-
mKeyboardEvent|private|-|-|-|Event::Keyboard|-
Mouse|public|-|-|-|enum|-
Keyboard|public|-|-|-|enum|-
getMouseEvent()|public|no|-|Event::Mouse|?|-
getKeyboardEvent()|public|no|-|Event::Keyboard|?|-

## EventHandler

var/func|access|abstract|parameters|return|functionality|threading
-|-|-|-|-|-|-
manageHandler()|private|no|-|-|subscribe/unsubscribe to EventDispatcher|-

## KeyboardEventHandler

var/func|access|abstract|parameters|return|functionality|threading
-|-|-|-|-|-|-
handleKeyboardEvent()|public|no|event:Event|bool|calls appropriate handler (that are user implemented)|-
setOnKeyDownHandler()|public|yes|event:Event|bool|set handler for a key pressed down|-
setOnKeyUpHandler()|public|yes|event:Event|bool|set handler for a key released|-
setOnKeyPressHandler()|public|yes|event:Event|bool|set handler for a key is press (down+up)|-
setOnMultpleKeyPressHandler()|public|yes|event:Event|bool|implement later|-

## MouseEventHandler

var/func|access|abstract|parameters|return|functionality|threading
-|-|-|-|-|-|-
handleMouseEvent()|public|no|event:Event|bool|calls appropriate handler (that are user implemented)|-
setOnLeftDownHandler()|public|yes|event:Event|bool|set handler for left button pressed down|-
setOnLeftUpHandler()|public|yes|event:Event|bool|set handler for left button released|-
setOnLightClickHandler()|public|yes|event:Event|bool|set handler for left button clicked|-
setOnRightDownHandler()|public|yes|event:Event|bool|set handler for right button pressed down|-
setOnRightUpHandler()|public|yes|event:Event|bool|set handler for right button released|-
setOnRightClickHandler()|public|yes|event:Event|bool|set handler for right button clicked|-

## EventDispatcher

var/func|access|abstract|parameters|return|functionality|threading
-|-|-|-|-|-|-
mEventHandlers|-|-|-|-|dictionary of vectors of subscribed EventHandlers|-
initializeEventDispatcher()|public|no|-|bool|initalize SDL event poller|-
pollEvents()|private|no|-|void|a daemon thread polling mouse/keyboard events|daemon
subscribeEventHandler(EventHandler)|public|no|EventHandler* const|bool|add EventHandler to mEventHandlers|-|
unsubscribeEventHandler(EventHandler)|public|no|EventHandler* const|bool|remove EventHandler to mEventHandlers|-|

---

## View: MouseEventHandler, KeyboardEventHandler

var/func|access|abstract|parameters|return|functionality|threading
-|-|-|-|-|-|-
mViewPort|private|-|-|-|store coordinate of top-right position of rectangle, it's width and height|-
mTexture|private|-|-|-|?|-
mColour|private|-|-|-|store RGBA of background|-
mText|private|-|-|-|?|-
getLeft()|public|no|-|double|?|-
getTop()|public|no|-|double|?|-
getWidth()|public|no|-|double|?|-
getHeight()|public|no|-|double|?|-
setFocus()|public|no|-|void|?|-



## ViewManager

var/func|parameters|return|functionality|threading
-|-|-|-|-
viewTree|-|-|map: hierarchical view-store|-|


---

## ViewParser

var/func|parameters|return|functionality|threading
-|-|-|-|-
parseView()|-|stringstream|parse->initialize view, return .cpp file|-|
