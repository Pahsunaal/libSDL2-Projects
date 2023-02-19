#pragma region TextManager

TextManager::TextManager(SDL_Renderer* renderer) : text_array{}, num_texts{}, renderer{ renderer } {
	printf("Created the textmanager\n");
}

TextManager::~TextManager() {
	for (size_t i{}; i < num_texts; i++) {
		delete text_array[i];
		text_array[i] = nullptr;
	}
	printf("Destroyed the textmanager\n");
}

Text* TextManager::createText(const char* fontpath, int size, const char* message, SDL_Color color) {
	// Catch errors on object creation
	try {
		if (num_texts > max_texts) return NULL; // Check if over max number of texts
		Text* text = new Text{ fontpath,size,message,color,renderer,num_texts };
		text_array[num_texts] = text; // Put the text in the text_array
		num_texts++;
		return text; // Return pointer to the created object
	} catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what());
		return NULL;
	}
}

Text* TextManager::createText(const char* fontpath, int size, const char* message, SDL_Color color, int width, int height) {
	try {
		if (num_texts > max_texts) return NULL;
		Text* text = new Text{ fontpath,size,message,color,renderer,width,height,num_texts };
		text_array[num_texts] = text;
		num_texts++;
		return text;
	} catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what());
		return NULL;
	}
}

void TextManager::destroyText(Text* text) {
	size_t index = text->index;

	if (text_array[index] != nullptr) delete text_array[index]; // Delete the Text object if it exists

	text_array[index] = nullptr; // Repoint the index to nullptr

	// Move adjacemt Text objects back one index
	for (size_t i{ index }; i < max_texts - 1 && i < num_texts - 1; i++) {
		text_array[i] = text_array[i + 1];
		text_array[i]->index--;
	}
	text_array[max_texts - 1] = nullptr;
	num_texts--;
}

#pragma endregion