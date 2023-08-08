//
//  prime.h
//  server
//
//  Created by Scott Gustafson on 7/1/16.
//  Copyright © 2016 Garlic Software LLC. All rights reserved.
//

namespace prime {
	
	// I built a couple types of strategies for fun that make lookups a bit faster.
	// see the performance tests, default is set to the fastest
	enum strategy {
		strategyDefault = 0, // the default is binary
		strategyLinear,
		strategyBinary,
		strategySieve
	};
	
	const bool is_prime(const unsigned int value, const strategy strat = strategyDefault);

}