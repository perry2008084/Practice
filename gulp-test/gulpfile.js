
var gulp = require('gulp');

gulp.task('copy', function(){
    gulp.src(['client/*.js', '!client/b*.js', 'client/bad.js'])
    .pipe(gulp.dest('build'));
});

gulp.task('default', function(){
   // default task
    //gulp.src('client/*.js')
    //    .pipe(gulp.dest('build'));

    var exec = require('child_process').exec;
    gulp.task('cmd', function(cb) {
      // build Jekyll
      exec('ls', function(err) {
        if (err) return cb(err); // return error
        cb(); // finished task
      });
    });
    
    var watcher = gulp.watch('client/*.js', ['copy']);
    watcher.on('change', function(event) {
      console.log('File ' + event.path + ' was ' + event.type + ', running tasks...');
    });
});