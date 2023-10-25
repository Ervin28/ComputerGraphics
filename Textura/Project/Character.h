#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

class Character {
public:
	Character();

	void SetIdleAnimations(const std::vector<std::string>& idleAnimations);
	void SetWalkAnimations(const std::vector<std::string>& walkAnimations);
	void SetAnimationState(const std::string& state);
	void UpdateAnimation();
	void Render();

private:
	std::vector<std::string> idleAnimations_;
	std::vector<std::string> walkAnimations_;
	std::string currentAnimationState_;
	int currentAnimationFrame_;
};

#endif  // CHARACTER_H
