def getKth(a, b, k)
    return b[k] if a.size == 0
    return a[k] if b.size == 0

    n = a.size / 2
    m = b.size / 2

    if a[n] > b[m]
        return getKth(b, a, k)
    end

    if n + m + 1 > k
        return getKth(a, b[0...m], k)
    else
        return getKth(a[n+1..-1], b, k - n - 1)
    end
end

# @param {Integer[]} nums1
# @param {Integer[]} nums2
# @return {Float}
def find_median_sorted_arrays(a, b)
    size = a.size + b.size
    (getKth(a, b, size / 2) + getKth(a, b, (size - 1) / 2)) * 0.5
end

