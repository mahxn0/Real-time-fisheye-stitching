#pragma once
#include <memory>
#include <vector>
#include "mat.h"
#include "stitcher_image.h"
#include "stitcherbase.h"
#include "match_info.h"
#include "matcher.h"

class Stitcher : public StitcherBase 
{
    public:
        template<typename U, typename X =disable_if_same_or_derived<Stitcher, U>>
        Stitcher(U&& i) : StitcherBase(std::forward<U>(i)) 
        {
            bundle.component.resize(imgs.size());
            for(size_t i=0;i<imgs.size();++i)
                bundle.component[i].imgptr = &imgs[i];
        }

        virtual Mat32f build();
    
	private:
		// transformation and metadata of each image
		ConnectedImages bundle;

		// 2d array of all matches
		// pairwise_matches[i][j].homo transform j to i
		std::vector<std::vector<MatchInfo> > pairwise_matches;

		// match two images
		bool match_image(const PairWiseMatcher&, int i, int j);

		// pairwise matching of all images
		void pairwise_match();
		// equivalent to pairwise_match when dealing with linear images
		void linear_pairwise_match();

		// assign a center to be identity
		void assign_center();

		// build by estimating camera parameters
		void estimate_camera();

		// naively build panorama assuming linear imgs
		void build_linear_simple();

		// for debug
		void draw_matchinfo() const;
		void dump_matchinfo(const char*) const;
		void load_matchinfo(const char*);
	
};


