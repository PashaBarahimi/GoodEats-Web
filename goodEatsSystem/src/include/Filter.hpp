#ifndef FILTER_HPP
#define FILTER_HPP

#include "Recipe.hpp"

#include <vector>
#include <string>

class Filter
{
public:
	enum class FilterIndex
	{
		TagFilter = 0,
		VegetarianFilter = 1,
		ReadyTimeFilter = 2,
		RatingFilter = 3
	};
	virtual std::vector<Recipe*> meetFilter(std::vector<Recipe*>& totalRecipes) const = 0;
	virtual ~Filter() = default;
};

class TagFilter : public Filter
{
public:
	TagFilter(std::string& tag);
	std::vector<Recipe*> meetFilter(std::vector<Recipe*>& totalRecipes) const override;
private:
	std::string tag_;
};

class VegetarianFilter : public Filter
{
public:
	std::vector<Recipe*> meetFilter(std::vector<Recipe*>& totalRecipes) const override;
};

class ReadyTimeFilter : public Filter
{
public:
	ReadyTimeFilter(int minMinutes, int maxMinutes);
	std::vector<Recipe*> meetFilter(std::vector<Recipe*>& totalRecipes) const override;
private:
	int minMinutes_;
	int maxMinutes_;
};

class RatingFilter : public Filter
{
public:
	RatingFilter(double minRating, double maxRating);
	std::vector<Recipe*> meetFilter(std::vector<Recipe*>& totalRecipes) const override;
private:
	double minRating_;
	double maxRating_;
};
#endif
