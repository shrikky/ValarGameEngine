#include "Maingame.h"
#include <Valar/GLTexture.h>
#include <iostream>
#include <Valar/Errors.h>
#include <Valar/ResourceManager.h>
#include <string>
#include <Valar/Valar.h>
#include <sstream> 
#include <glm/gtc/type_ptr.hpp>

MainGame::MainGame() :_screenWidth(1024), _screenHeight(800), _currentGameState(GameState::PLAY), _time(0)
{
	_maxFPS =60;
	_camera.Init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
	_currentGameState = GameState::PLAY;
}

void MainGame::Run()
{
	InitSystems();
	GameLoop();
}

void MainGame::InitSystems()
{
	Valar::Init();
	_window.Create("GamEngine", _screenWidth, _screenHeight, Valar::BORDERLESS);
	 InitShaders();
	 _spriteBatch.Init();
	 _fpsLimiter.Init(_maxFPS);
}

void MainGame::GameLoop()
{
	while (_currentGameState != GameState::EXIT)
	{
		_fpsLimiter.Begin();
		ProcessInput();
		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].Update() == true )
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
			{
				i++;
			}
		}
		_time += 0.1f;
		_camera.Update();
		DrawGame();

		_fps = _fpsLimiter.End();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << ::std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::ProcessInput()
{
	SDL_Event evnt;
	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
		_currentGameState = GameState::EXIT;
		break;
		case SDL_MOUSEMOTION:
			_inputManager.SetMouseCoords(evnt.motion.x,evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.PressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.ReleaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.PressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.ReleaseKey(evnt.button.button);
			break;

		default:
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.SetScale(_camera.GetScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.SetScale(_camera.GetScale() - SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.GetMouseCoords();
		mouseCoords = _camera.ScreenToWorld(mouseCoords);


		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);
		_bullets.emplace_back(playerPosition, direction, 5.0f, 1000);

		std::cout << mouseCoords.x << " " << mouseCoords.y<<std::endl;
	}

}

void MainGame::DrawGame()
{
	  //Set the base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable the shader
	 _colorProgram.Use();

	//We are using texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Get the uniform location
	GLuint texLocation = _colorProgram.GetUnitformLocation("playerTexture");
	//Tell the shader that the texture is in texture unit 0
	glUniform1i(texLocation, 0);

	//Set the camera matrix
	GLint pLocation = _colorProgram.GetUnitformLocation("proj");
	glm::mat4 cameraMatrix = _camera.GetCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.Begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Valar::GLTexture texture = Valar::ResourceManager::GetTexture("Textures/PNG/CharacterRight_Standing.png");
	Valar::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.Draw(pos, uv, texture.id, 0.0f, color);

	for (size_t i = 0; i < _bullets.size(); i++) {
		_bullets[i].Draw(_spriteBatch);
	}

	_spriteBatch.End();

	_spriteBatch.RenderBatch();

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//disable the shader
	_colorProgram.Unuse();

	//Swap our buffer and draw everything to the screen!
	_window.SwapBuffer();
}

void MainGame::InitShaders()
{
	_colorProgram.CompileShaders("Shaders/VertexShader.vs","Shaders/FragmentShader.fs");
	_colorProgram.AddAttribute("vertexPosition");
	_colorProgram.AddAttribute("vertexColor");
	_colorProgram.AddAttribute("vertexUV");
	_colorProgram.LinkShaders();

}

