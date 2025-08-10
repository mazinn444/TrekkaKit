# Guide

## How to use Common

Defines basic types:

* **Position**: 2D position with `x` and `y` as floats.
* **Box**: width and height as floats.
* **Geometry**: width and height as integers.
* **Enums Key and MouseButton**: to use with Input.

---

## How to use Input

Easy keyboard and mouse reading:

* Create `Input` passing the SFML window pointer:

  ```cpp
  Input input(&window);
  ```
* Update input state inside the loop:

  ```cpp
  input.update();
  ```
* Check if a key is pressed (held down):

  ```cpp
  input.isKeyPressed(Key::A);
  ```
* Check if a key was just clicked (pressed this frame only):

  ```cpp
  input.isKeyClick(Key::Enter);
  ```
* Same for mouse buttons:

  ```cpp
  input.isMousePressed(MouseButton::Left);
  input.isMouseClick(MouseButton::Left);
  ```
* Get mouse position inside the window:

  ```cpp
  Position p = input.getMousePosition();
  ```

---

## How to use Animation

Animate sprites by slicing a horizontal sprite sheet.

* Create with frame size, count, and FPS:

  ```cpp
  Animation anim(frameWidth, frameHeight, frameCount, fps);
  ```
* Update in the loop passing delta time:

  ```cpp
  anim.update(dt);
  ```
* Get the current frame rectangle to apply on the sprite:

  ```cpp
  sprite.setTextureRect(anim.getFrameRect());
  ```

---

## How to use Entity

Represents an object on screen with sprite, position, collision, and animation.

* Create passing image, box (hitbox), and position:

  ```cpp
  Entity player("player.png", Box(64,64), Position(100, 200));
  ```
* Update all logic (including animation):

  ```cpp
  player.update(dt);
  ```
* Draw on the window:

  ```cpp
  player.draw(window);
  ```
* Move by delta:

  ```cpp
  player.moveBy(dx, dy);
  ```
* Check collision with another entity:

  ```cpp
  if (player.collide(enemy)) { ... }
  ```
* Set animation:

  ```cpp
  player.setAnimation(&anim);
  ```
* Set custom collision box:

  ```cpp
  player.setCollisionBox(offsetX, offsetY, width, height);
  ```
* Reset collision box to default:

  ```cpp
  player.clearCollisionBox();
  ```

---

## How to use Camera

Controls the window view (zoom, position).

* Access via `game.getCamera()`.
* Move the camera:

  ```cpp
  camera.move(dx, dy);
  ```
* Set camera position:

  ```cpp
  camera.setPosition(x, y);
  ```
* Zoom in/out:

  ```cpp
  camera.zoom(factor);
  ```
* The camera automatically applies the view to the window.

---

## How to use Font

Loads a system font for debug text.

* Just call `loadSystemFont()` and use the returned font.

---

## How to use Game

Everything that controls the game (window, loop, input, FPS, drawing).

* Create with title, size, resizable, FPS:

  ```cpp
  Game game("My Game", Geometry(800, 600), true, 60);
  ```
* Basic game loop:

  ```cpp
  while (game.isRunning()) {
      game.pollEvents();
      float dt = game.restartDelta();

      // logic, input, update

      game.clear();
      // draw entities
      game.display();
  }
  ```
* Get input:

  ```cpp
  auto& input = game.getInput();
  ```
* Draw text:

  ```cpp
  game.drawText("Hello!", 100, 100, 20, sf::Color::Green);
  ```
* Set background color:

  ```cpp
  game.setClearColor(sf::Color::Blue);
  ```
* Show FPS (there’s also a function in Debug for this).

---

## How to use Timer

Simple timer for callbacks based on time.

* Create a timer:

  ```cpp
  Timer t;
  t.startTimer(1000, []() { std::cout << "1 second passed\n"; }, true);
  ```
* Check if done:

  ```cpp
  if (t.isDone()) { /* callback was called */ }
  ```
* Stop and reset:

  ```cpp
  t.reset();
  ```

---

## How to use Debug

Useful stuff for debugging:

* Show and update FPS:

  ```cpp
  Debug::showAndUpdateFPS(game, dt);
  ```
* Show an entity’s collision box:

  ```cpp
  Debug::showCollisionBox(entity, game);
  ```
* Show grid on screen (good to see cells):

  ```cpp
  Debug::showGrid(game, 32);
  ```
* Log entity info:

  ```cpp
  Debug::logEntityInfo(entity, "Player");
  ```

---

# Final tips

* Always call `game.pollEvents()` to process events.
* Update input with `input.update()`, usually inside `game.pollEvents()`.
* Pass `dt` (delta time) to update entities and animations.
* Control camera via `game.getCamera()`.
* Use `Timer` for timed tasks without blocking the game.
* Check collisions with `Entity::collide`.
* Use Debug to make development easier.