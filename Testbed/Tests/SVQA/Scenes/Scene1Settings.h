#pragma once

#include "Settings.h"

namespace svqa
{
	struct Scene1Settings : Settings
	{
		typedef std::shared_ptr<Scene1Settings> Ptr;

		Scene1Settings() {}

		int numberOfObjects;
		int numberOfObstacles;

		void to_json(json& j) {
			j.emplace("numberOfObjects", this->numberOfObjects);
			j.emplace("numberOfObstacles", this->numberOfObstacles);
			Settings::to_json(j);
		}

		void from_json(const json& j) {
			Settings::from_json(j);
			j.at("numberOfObjects").get_to(this->numberOfObjects);
			j.at("numberOfObstacles").get_to(this->numberOfObstacles);
		}
	};
}