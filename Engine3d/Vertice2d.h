#pragma once
class Vertice2d {
	public:
		float u;
		float v;

		Vertice2d();
		Vertice2d(float u, float v);

		static Vertice2d intersect(const Vertice2d& inside, const Vertice2d& outside, const float t);
};

