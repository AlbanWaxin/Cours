class Solde {
    value;
  unit;
    errorMargin;

    neutral(unit) {
        return new Solde(0., unit, 0.);
    }

    constructor (value, unit, errorMargin) {
        this.value = value;
        this.unit = unit;
        this.errorMargin = errorMargin;
    }

    add(coefficient,  other) {
        return this.add(other.times(coefficient));
    }

    add(other) {
        if (!(this.unit==other.unit))
            throw new Error(
                    "Cannot add amounts of different units: " + this.unit + " <> " + other.unit);
        return new Solde(+this.value +  +other.value, this.unit, this.errorMargin + other.errorMargin);
    }

    times(coefficient) {
        return new Solde(coefficient * this.value, this.unit, coefficient * this.errorMargin);
    }

    equals(other) {
        return Math.abs(this.value - other.value) <= 0.01 && (this.unit==other.unit)
                && Math.abs(this.errorMargin - other.errorMargin) <= 0.1;
    }

    toString() {
        return this.value + (this.errorMargin == 0. ? "" : "+/-" + this.errorMargin) + " " + this.unit;
    }
}

let solde = new Solde(1.0, "€", 0.1);
let e = solde.neutral("€");
let total = (new Solde(10, "€", 0.1)).add(new Solde(20, "€", 0.1));
console.log(e);
console.log(total);

