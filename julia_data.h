#pragma once

namespace julia
{
	//Data
	const int SIZE = 500;
	int data[SIZE * SIZE] = { 0 };
	bool paused = true;
	constexpr float PI = 3.14159265;

	//Resolution
	int res = 25;
	float radius = 2.0;
	float bias[2] = { 0.0 };
	double zoom = 1;
	int order = 3;
	double px = 0.0;
	double py = 0.0;

	float cc[4] = { 0.f, 0.86, 0.91, 1.0 };
	float dc[4] = { 0.1f, 0.f, 0.1f, 1.0 };

	bool active = false;
	bool appear = false;
	float appearAmp = 1.0;
	bool movex = false;
	bool movey = false;
	float phase[2] = { 0.5, 0.5 };
	float amplitude[2] = { 0.5f };
	float center[2] = { 0.0, 0.0 };
	float rate = 0.01;
	float t = 0.0;
}