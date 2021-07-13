function rangeCheck(minRange, maxRange, minIsChanged, valueLabel) {
    if (minIsChanged == true) {
        if (minRange.valueAsNumber > maxRange.valueAsNumber) {
            alert("Minimum can't be more than Maximum!");
            minRange.value=minRange.min;
        }
        valueLabel.innerHTML = minRange.value;
    }
    else {
        if (maxRange.valueAsNumber < minRange.valueAsNumber) {
            alert("Maximum can't be less than Minimum!");
            maxRange.value=maxRange.max;
        }
        valueLabel.innerHTML = maxRange.value;
    }
}

function resetFilter(){
    document.getElementById("resetFilterForm").submit();
}