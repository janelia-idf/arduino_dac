$(function() {
    var milli_volt = 0;

    $(':button').button();

    $("#sliderDacAVoltage").slider({
        range: "min",
        value: milli_volt,
        min: 0,
        max: 5000,
        step: 250
    });
    $("#displayDacAVoltage").text(milli_volt + "mV");
    $("#sliderDacAVoltage").on("slide",
                               function( event, ui ) {
                                   milli_volt = ui.value;
                                   $("#displayDacAVoltage").text(ui.value + "mV");
                                   Sijax.request('analogWriteA',[milli_volt]);
                               });

    $('#sineWave').click(function () {
        Sijax.request('startWaveform',[0]);
    });
    $('#triangleWave').click(function () {
        Sijax.request('startWaveform',[1]);
    });
    $('#sawtoothWave').click(function () {
        Sijax.request('startWaveform',[2]);
    });
    $('#squareWave').click(function () {
        Sijax.request('startWaveform',[3]);
    });
    $('#stopWaveform').click(function () {
        Sijax.request('stopWaveform');
        Sijax.request('analogWriteA',[0]);
        $("#displayDacAVoltage").text("0mV");
        $("#sliderDacAVoltage").slider('value', 0);
    });

});
