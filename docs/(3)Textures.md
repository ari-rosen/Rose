# Textures
A texture can be create by using a scene's ```createTexture``` method, along with an image
```cpp
private:
	Rose::TextureID texture;
public:
	void onStart() override {
		texture = createTexture("image.png");
	}
```
Optionally, a ```Rose::TextureParameter``` can be specified as well.

Rose defaults to filtering images using linear interpolation, which can make pixel art look fuzzy. To specify a custom filtering mode, create a ```Rose::TextureParameter``` and use it as a second argument in ```createTexture```. Pixel art looks best with a ```Nearest``` filter.
```cpp
const Rose::TextureParameter pixelArtParam = {
	Rose::WrapMode::Repeat,
	Rose::WrapMode::Repeat,
	Rose::FilterMode::LinearMipmapNearest 
	Rose::FilterMode::Nearest
};
texture = createTexture("image.png", pixelArtParam);
```
To bind a ```Rose::TextureID``` to a ```Rose::GameObject```, use ```Rose::SpriteComponent```
```cpp
addComponents<Rose::SpriteComponent>(exampleObject);
Rose::SpriteComponent exampleSprite = {
	.TextureID = texture 
};
insertComponentData(exampleObject, exampleSprite);
```
