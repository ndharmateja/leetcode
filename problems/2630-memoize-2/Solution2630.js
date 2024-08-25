/**
 * @param {Function} fn
 * @return {Function}
 */
function memoize(fn) {
    function containsKey(map, argsList) {
        for(const [currArgsList, _] of map.entries()) {
            if (currArgsList.length !== argsList.length) continue;
            let isMatch = true;
            for(let i = 0; i < argsList.length; i++) {
                if (argsList[i] !== currArgsList[i]) {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch) return true;
        }
        return false;
    }

    function getValue(map, argsList) {
        for(const [currArgsList, value] of map.entries()) {
            if (currArgsList.length !== argsList.length) continue;
            let isMatch = true;
            for(let i = 0; i < argsList.length; i++) {
                if (argsList[i] !== currArgsList[i]) {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch) return value;
        }
        return false;
    }

    const memo = new Map()
    return function(...args) {
        // If result has already been computed, return it
        if (containsKey(memo, args)) return getValue(memo, args)

        // If not compute and store it, and return it
        var result = fn(...args)
        memo.set(args, result)
        return result
    }
}


/** 
 * let callCount = 0;
 * const memoizedFn = memoize(function (a, b) {
 *	 callCount += 1;
 *   return a + b;
 * })
 * memoizedFn(2, 3) // 5
 * memoizedFn(2, 3) // 5
 * console.log(callCount) // 1 
 */