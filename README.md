For a [cooking website][3] I recently worked on,
I needed to display decimal floating point numbers as fractions. I needed to
come up with the fraction closest to what the user typed. For example, 0.33
should resolve to ⅓. When I googled for a solution, most of the code I found
was slow, buggy, and worst of all, too precise (returning 33/100 for the above example.)

I decided to widen my search to C, and [found][1] a piece of code on Stack Overflow
written by David Eppstein in 1993.
It uses the [theory of continued fractions][2] to approach the correct value,
but stops when the denominator reaches some value. The limitation of such an
algorithm is that we can't choose to leave out unnatural denominators

So became `fraction`: it's Eppstein's code in a Ruby gem.

Install it with `gem`:

    gem install fraction

Using this gem is easy:

    require 'fraction'
    fraction = 0.33.to_fraction   # Fraction object
    fraction.numerator == 1
    fraction.denominator == 3

You can get the HTML entities associated with the fraction. If it can't find any, it will return the fraction in the format n/d
    fraction.to_html # 1/3

The best part of this gem over others is the speed:

    % ruby test.rb
    I'm Feeling Lucky: 19.145s
    'fraction' gem: 2.090s

subtracting the time required for an empty ruby loop, we can conclude the
algorithm itself requires only ½ of a second for 1,000,000 iterations on my Mac Pro.


[1]: http://stackoverflow.com/questions/95727/how-to-convert-floats-to-human-readable-fractions
[2]: http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/cfINTRO.html#termdecs
[3]: http://freshslowcooking.com
