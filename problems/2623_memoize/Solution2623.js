/**
 * @param {Function} fn
 * @return {Function}
 */
function memoize(fn) {
    const memo = new Map()
    return function(...args) {
        // Get the unique of fn + args
        var key = fn.name + JSON.stringify(args)

        // If result has already been computed, return it
        if (memo.has(key)) return memo.get(key)

        // If not compute and store it, and return it
        var result = fn(...args)
        memo.set(key, result)
        return result
    }
}