var customName = document.getElementById('customName');
var randomize = document.querySelector('.randomize');
var story = document.querySelector('.story');

var storyText = 'It was 94 fahrenheit outside, so :insertx: went for a walk. \
    When they got to :inserty:, they stared in horror for a few moments, then \
    :insertz:. Bob saw the whole thing, but was not surprised — :insertx: weighs \
    300 pounds, and it was a hot day.';
var insertX = 'Willy the Goblin |\
    Big Daddy |\
    Father Christmas'.split('|');
var insertY = 'the soup kitchen |\
    Disneyland |\
    the White House'.split('|');
var insertZ = 'spontaneously combusted |\
    melted into a puddle on the sidewalk |\
    turned into a slug and crawled away'.split('|');


function randomValueFromArray(array){
    return array[Math.floor(Math.random()*array.length)];
}

randomize.addEventListener('click', function () {
    var newStory = storyText;
    var item = {
        x: randomValueFromArray(insertX),
        y: randomValueFromArray(insertY),
        z: randomValueFromArray(insertZ)
    };

    newStory = newStory.replace(/:insertx:/g, item.x);
    newStory = newStory.replace(':inserty:', item.y);
    newStory = newStory.replace(':insertz:', item.z);

    if(customName.value != '') {
        newStory = newStory.replace ('Bob', customName.value);
    }
    if(document.getElementById("uk").checked) {
        newStory = newStory.replace('300 pounds', Math.round(300 * 0.0714286) + ' stone');
        newStory = newStory.replace('94 fahrenheit', Math.round((94 - 32) * 5 / 9) + ' centigrade');
    }
    story.textContent = newStory;
    story.style.visibility = 'visible';
});
