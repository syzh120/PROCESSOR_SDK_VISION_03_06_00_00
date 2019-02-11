/*
 *  ======== getString ========
 *  Default implementation of getString method
 */
function getString(sep)
{
    if (sep == null) {
        sep = '.';
    }
    
    function fixedWidth(num, width)
    {
        if (width == null) {
            width = 2;
        }
        var len = width - String(num).length;
        return (len <= 0 ? num : ("000000000000".substring(0, len) + num));
    }
    
    return (this.MAJOR
        + sep + fixedWidth(this.MINOR, this.WIDTH)
        + sep + fixedWidth(this.PATCH, this.WIDTH));
}

